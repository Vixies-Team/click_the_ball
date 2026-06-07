#include <stdio.h>
#include "../../vendor/raylib/include/raylib.h"

#include "options.h"

#include "../ui/slider.h"
#include "../ui/label.h"

#include "../core/game.h"
#include "../core/scene.h"

#include "../audio/audio.h"

#include "gameplay.h"

static bool is_already_init = false;

static UISlider musicSlider;
static UISlider sfxSlider;

static UILabel optionsLabel;
static UILabel musicLabel;
static UILabel musicPercentageLabel;
static UILabel sfxLabel;
static UILabel sfxPercentageLabel;
static UILabel backLabel;

static char musicPercentageText[5];
static char sfxPercentageText[5];

static int selected = 0;

#define OPTION_MUSIC  0
#define OPTION_SFX    1
#define OPTION_BACK   2

void SetSFXVolume(float value) {
    SetSoundVolume(selectSfx, value / 100.0f);
    SetSoundVolume(menuSfx, value / 100.0f);
    PlaySound(selectSfx);
}

void OptionsInit() {
    if (!is_already_init) {
        is_already_init = true;

        musicSlider = (UISlider){
            .rect = { 60, 140, 250, 20 },
            .min = 0,
            .max = 100,
            .value = 100
        };

        sfxSlider = (UISlider){
            .rect = { 60, 240, 250, 20 },
            .min = 0,
            .max = 100,
            .value = 100,
        };

        UILabelInit(&optionsLabel, "OPTIONS", UI_LABEL_TYPE_NORMAL, (Vector2){60, 40}, 40, WHITE, 0.0f);
        UILabelInit(&musicLabel, "Music", UI_LABEL_TYPE_NORMAL, (Vector2){60, 100}, 30, WHITE, 0.0f);
        UILabelInit(&musicPercentageLabel, musicPercentageText, UI_LABEL_TYPE_NORMAL, (Vector2){330, 132}, 20, GRAY, 0.0f);
        UILabelInit(&sfxLabel, "SFX", UI_LABEL_TYPE_NORMAL, (Vector2){60, 200}, 30, WHITE, 0.0f);
        UILabelInit(&sfxPercentageLabel, sfxPercentageText, UI_LABEL_TYPE_NORMAL, (Vector2){330, 232}, 20, GRAY, 0.0f);
        UILabelInit(&backLabel, "Back", UI_LABEL_TYPE_NORMAL, (Vector2){60, 340}, 30, WHITE, 0.0f);

        snprintf(musicPercentageText, sizeof(musicPercentageText), "%d%%", musicSlider.value);
        snprintf(sfxPercentageText, sizeof(musicPercentageText), "%d%%", sfxSlider.value);
    }
}

void BackScene() {
    selected = 0;
    if (!is_gameplay) ChangeScene(SCENE_MENU);
    else ChangeScene(SCENE_GAMEPLAY);
    PlaySound(selectSfx);
}

void OptionsUpdate() {
    switch(SliderUpdate(&musicSlider)) {
        case SLIDER_EVENT_NONE: break;
        case SLIDER_EVENT_CLICKED: break;
        case SLIDER_EVENT_DRAGGED: {
            SetMusicVolume(songMusic, (musicSlider.value / 100.0f) / (is_paused ? 2.0f : 1.0f));
            snprintf(musicPercentageText, sizeof(musicPercentageText), "%d%%", musicSlider.value);
            break;
        };
        case SLIDER_EVENT_RELEASED: break;
    }
    
    switch(SliderUpdate(&sfxSlider)) {
        case SLIDER_EVENT_NONE: break;
        case SLIDER_EVENT_CLICKED: break;
        case SLIDER_EVENT_DRAGGED: {
            snprintf(sfxPercentageText, sizeof(sfxPercentageText), "%d%%", sfxSlider.value);
            break;
        };
        case SLIDER_EVENT_RELEASED: {
            SetSFXVolume(sfxSlider.value);
            break;
        };
    }
    
    if (IsKeyPressed(KEY_DOWN)) {
        selected++;
        if (selected > OPTION_BACK) selected = 0;
        PlaySound(menuSfx);
    }
    else if (IsKeyPressed(KEY_UP)) {
        selected--;
        if (selected < 0) selected = OPTION_BACK;
        PlaySound(menuSfx);
    }
    else if (IsKeyPressed(KEY_ESCAPE)) BackScene();

    switch(selected) {
        case OPTION_MUSIC: {
            if (IsKeyDown(KEY_RIGHT)) {
                musicSlider.value++;
                if (musicSlider.value > musicSlider.max) musicSlider.value = musicSlider.max;
                snprintf(musicPercentageText, sizeof(musicPercentageText), "%d%%", musicSlider.value);
                SetMusicVolume(songMusic, (musicSlider.value / 100.0f) / (is_paused ? 2.0f : 1.0f));
            } else if (IsKeyDown(KEY_LEFT)) {
                musicSlider.value--;
                if (musicSlider.value < musicSlider.min) musicSlider.value = musicSlider.min;
                snprintf(musicPercentageText, sizeof(musicPercentageText), "%d%%", musicSlider.value);
                SetMusicVolume(songMusic, (musicSlider.value / 100.0f) / (is_paused ? 2.0f : 1.0f));
            }
            break;
        }
        case OPTION_SFX: {
            if (IsKeyDown(KEY_RIGHT)) {
                sfxSlider.value++;
                if (sfxSlider.value > sfxSlider.max) sfxSlider.value = sfxSlider.max;
                snprintf(sfxPercentageText, sizeof(sfxPercentageText), "%d%%", sfxSlider.value);
            } else if (IsKeyDown(KEY_LEFT)) {
                sfxSlider.value--;
                if (sfxSlider.value < sfxSlider.min) sfxSlider.value = sfxSlider.min;
                snprintf(sfxPercentageText, sizeof(sfxPercentageText), "%d%%", sfxSlider.value);
            } else if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)) SetSFXVolume(sfxSlider.value);
            break;
        }
        case OPTION_BACK: {
            if (IsKeyPressed(KEY_ENTER)) BackScene();
            break;
        }
    }
}

void OptionsDrawing() {
    ClearBackground(BLACK);

    UILabelDraw(&optionsLabel);

    musicLabel.color = selected == OPTION_MUSIC ? YELLOW : WHITE;
    UILabelDraw(&musicLabel);
    SliderDraw(&musicSlider);
    UILabelDraw(&musicPercentageLabel);

    sfxLabel.color = selected == OPTION_SFX ? YELLOW : WHITE;
    UILabelDraw(&sfxLabel);
    SliderDraw(&sfxSlider);
    UILabelDraw(&sfxPercentageLabel);

    backLabel.color = selected == OPTION_BACK ? YELLOW : WHITE;
    UILabelDraw(&backLabel);
}

float GetSFXVolume() {
    return sfxSlider.value / 100.0f;
}

float GetMusicVolume() {
    return musicSlider.value / 100.0f;
}

void OptionsDeinit() {

}
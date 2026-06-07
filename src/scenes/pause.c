#include <stdio.h>
#include <math.h>
#include "../../vendor/raylib/include/raylib.h"

#include "pause.h"

#include "../core/config.h"
#include "../core/scene.h"
#include "../core/game.h"

#include "../ui/label.h"

#include "../effects/fade.h"

#include "../audio/audio.h"
#include "../audio/audio_fade.h"

#include "../scenes/gameplay.h"
#include "../scenes/menu.h"
#include "../scenes/options.h"

#define MENU_SIZE 3

static int selected = 0;
static const char *menuItems[] = {
    "Resume Game",
    "Options",
    "Back to Menu"
};

static UILabel titlelabel;
static UILabel menuLabel[MENU_SIZE];

static fade pauseFade;

void PauseInit() {
    FadeInit(&pauseFade);

    UILabelInit(&titlelabel, "GAME PAUSED", UI_LABEL_TYPE_NORMAL, (Vector2){0, 0}, 40, WHITE, 0.0f);
    titlelabel.position = (Vector2){SCREEN_WIDTH / 2 - UILabelMeasure(&titlelabel).x / 2, 80};
    for (int a = 0; a < MENU_SIZE; a++) {
        UILabelInit(&menuLabel[a], menuItems[a], UI_LABEL_TYPE_NORMAL, (Vector2){0, 0}, 30, WHITE, 0.0f);
        menuLabel[a].position = (Vector2){SCREEN_WIDTH / 2 - UILabelMeasure(&menuLabel[a]).x / 2, 180 + (a * 50)};
    }

    SetMusicVolume(songMusic, GetMusicVolume() / 2.0f);
}

void PauseUpdate() {
    if (!pauseFade.active) {
        if (IsKeyPressed(KEY_DOWN)) {
            selected++;
            if (selected >= MENU_SIZE) selected = 0;
            PlaySound(menuSfx);
        }
        else if (IsKeyPressed(KEY_UP)) {
            selected--;
            if (selected < 0) selected = MENU_SIZE - 1;
            PlaySound(menuSfx);
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            PlaySound(selectSfx);
            switch(selected) {
                case 0: {
                    is_paused = false;
                    PauseDeinit();
                    break;
                }   
                case 1: {
                    ChangeScene(SCENE_OPTIONS);
                    break;
                }
                case 2: {
                    AudioFadeStart(&musicFade, AUDIO_FADE_OUT, 1.5f, GetMusicVolume() / 2.0f, 0.0f);
                    FadeStart(&pauseFade, FADE_OUT, 1.5f, BLACK);
                    break;
                }
            }
        }
    }

    if (FadeUpdate(&pauseFade) == FADE_EVENT_FINISHED && pauseFade.mode == FADE_OUT) {
        if (selected == 2) {
            PauseDeinit();
            GameplayDeinit();
            MenuInit();
            ChangeScene(SCENE_MENU);
        }
    }
}
void PauseDrawing() {
    ClearBackground(BLACK);

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5));

    UILabelDraw(&titlelabel);

    for (int a = 0; a < MENU_SIZE; a++) {
        menuLabel[a].color = a == selected ? YELLOW : GRAY;
        UILabelDraw(&menuLabel[a]);
    }

    FadeDraw(&pauseFade);
}

void PauseDeinit() {
    SetMusicVolume(songMusic, GetMusicVolume());
    selected = 0;
}
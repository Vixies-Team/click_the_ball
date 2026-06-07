#include <stdio.h>
#include <string.h>

#include "../../vendor/raylib/include/raylib.h"

#include "intro.h"

#include "../audio/audio.h"

#include "../core/config.h"
#include "../core/game.h"

#include "../ui/label.h"

#include "../effects/fade.h"

#include "../utils/timer.h"

#include <stdlib.h>

static fade introFade;

static UILabel titleLabel;
static UILabel presentLabel;

static Timer presentTimer;
static Timer fadeTimer;

void IntroInit() {
    FadeInit(&introFade);

    TimerInit(&presentTimer, 1.0f);
    TimerInit(&fadeTimer, 2.0f);

    UILabelInit(&titleLabel, "Vixies Studio", UI_LABEL_TYPE_SUBTEXT, (Vector2){0}, 50, WHITE, 0.15f);
    UILabelInit(&presentLabel, "Present", UI_LABEL_TYPE_NORMAL, (Vector2){0}, 25, (Color){180, 180, 180, 0}, 0.0f);
    
    titleLabel.position = (Vector2){(SCREEN_WIDTH / 2) - (UILabelMeasure(&titleLabel).x / 2), (SCREEN_HEIGHT / 2) - 30};
    presentLabel.position = (Vector2){(SCREEN_WIDTH / 2) - (UILabelMeasure(&presentLabel).x / 2), (SCREEN_HEIGHT / 2) + 35};

    presentLabel.alpha = 0.0f;
}

void IntroUpdate() {
    if (IsKeyPressed(KEY_ENTER) && !introFade.active) FadeStart(&introFade, FADE_OUT, 1.0f, BLACK);

    switch(UILabelUpdate(&titleLabel, GetFrameTime())) {
        case UI_LABEL_EVENT_NONE: break;
        case UI_LABEL_EVENT_TYPING: {
            if (titleLabel.subtext.char_show != ' ') {
                SetSoundPitch(talkingSfx, GetRandomValue(45, 55) / 100.0f);
                PlaySound(talkingSfx);
            }
            break;
        }
        case UI_LABEL_EVENT_DONE: {
            TimerStart(&presentTimer);
            break;
        }
    }

    if (TimerUpdate(&presentTimer, GetFrameTime()) == TIMER_EVENT_FINISHED) {
        TimerStart(&fadeTimer);
        presentLabel.alpha = 1.0f;
        PlaySound(selectSfx);
    }
    if (TimerUpdate(&fadeTimer, GetFrameTime())) FadeStart(&introFade, FADE_OUT, 1.0f, BLACK);

    switch(FadeUpdate(&introFade)) {
        case FADE_EVENT_FINISHED: {
            ChangeScene(SCENE_MENU);
            break;
        }
        case FADE_EVENT_NONE: break;
    }
}
void IntroDrawing() {
    ClearBackground(BLACK);
    
    UILabelDraw(&titleLabel);
    UILabelDraw(&presentLabel);
    
    FadeDraw(&introFade);
}

void IntroDeinit() {

}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../../vendor/raylib/include/raylib.h"

#include "gameplay.h"

#include "../core/game.h"
#include "../core/scene.h"
#include "../core/config.h"

#include "../platform/window.h"

#include "../audio/audio.h"
#include "../audio/audio_fade.h"

#include "../utils/utils.h"
#include "../utils/timer.h"

#include "../entities/ball.h"
#include "../ui/label.h"
#include "../effects/fade.h"

#include "../scenes/pause.h"
#include "../scenes/options.h"

#define BALL_COUNT 5

static unsigned int score = 0;
static unsigned int highScore = 0;
static char scoreText[32];
static char highScoreText[32];
bool is_paused = false;
bool is_gameplay = false;

static UILabel scoreLabel;
static UILabel highScoreLabel;

static fade gameplayFade;

static UILabel label1;

static Timer label1Next;
static Timer label1Wait;

AudioFade musicFade;

void GameplayInit() {
    score = 0;

    AudioFadeInit(&musicFade, AUDIO_TYPE_MUSIC, &songMusic);
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    snprintf(highScoreText, sizeof(highScoreText), "High Score: %d", highScore);

    UILabelInit(&scoreLabel, scoreText, UI_LABEL_TYPE_NORMAL, (Vector2){20, 20}, 20, WHITE, 0.0f);
    UILabelInit(&highScoreLabel, highScoreText, UI_LABEL_TYPE_NORMAL, (Vector2){0, 0}, 20, WHITE, 0.0f);
    highScoreLabel.position = (Vector2){SCREEN_WIDTH - UILabelMeasure(&highScoreLabel).x - 20, 20};

    is_paused = false;
    is_gameplay = true;

    FadeStart(&gameplayFade, FADE_IN, 1.0f, BLACK);
    AudioFadeStart(&musicFade, AUDIO_FADE_IN, 1.0f, 0.0f, GetMusicVolume());
    PlayMusicStream(songMusic);

    label1Next = (Timer){0};
    label1Wait = (Timer){0};
    UILabelInit(&label1, "Hello, Player! Welcome to this game. in this game, you just simply touch the ball.", UI_LABEL_TYPE_SUBTEXT, (Vector2){0, 0}, 20, WHITE, 0.09f);
}

void GameplayUpdate() {
    FadeUpdate(&gameplayFade);
    AudioFadeUpdate(&musicFade);

    if (gameplayFade.active) return; // intinya kalo gameplayFade nya masih nyala, berarti game nya jangan mulai aja dulu. 

    if (is_paused) PauseUpdate();
    else {
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (is_paused) {
                is_paused = false;
                PauseDeinit();
            }
            else {
                is_paused = true;
                PauseInit();
            }
        }

        TimerUpdate(&label1Wait, GetFrameTime());
        if (!label1Wait.active) {
            switch(UILabelUpdate(&label1, GetFrameTime())) {
                case UI_LABEL_EVENT_NONE: break;
                case UI_LABEL_EVENT_TYPING: {
                    const char* visibleText = TextSubtext(label1.text, 0, label1.subtext.text_visible);
                    int textWidth = MeasureText(visibleText, 20); 
                    label1.position = (Vector2){(SCREEN_WIDTH / 2) - (textWidth / 2), (SCREEN_HEIGHT / 2)};

                    if (label1.subtext.char_show == '!' || label1.subtext.char_show == '.') {
                        TimerInit(&label1Wait, 0.25);
                        TimerStart(&label1Wait);
                    }
                    else if (label1.subtext.char_show == ',') {
                        TimerInit(&label1Wait, 0.1);
                        TimerStart(&label1Wait);
                    }
                    else if (label1.subtext.char_show != ' ') {
                        PlaySound(talkingSfx);
                        SetSoundPitch(talkingSfx, GetRandomValue(45, 55) / 100.0f);
                    }
                    break;
                }
                case UI_LABEL_EVENT_DONE: {

                }
            }
        }
        
    }
}
void GameplayDrawing() {
    ClearBackground(BLACK);
    
    UILabelDraw(&scoreLabel);
    UILabelDraw(&highScoreLabel);

    DrawLine(0, 50, SCREEN_WIDTH, 50, WHITE);

    UILabelDraw(&label1);

    FadeDraw(&gameplayFade);

    if (is_paused) PauseDrawing();
}

void GameplayDeinit() { 
    is_gameplay = false;
    is_paused = false;
    StopMusicStream(songMusic);
}
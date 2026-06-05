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

#include "../entities/ball.h"
#include "../utils/utils.h"
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

AudioFade musicFade;

void GameplayInit() {
    score = 0;

    AudioFadeInit(&musicFade, AUDIO_TYPE_MUSIC, &songMusic);
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    snprintf(highScoreText, sizeof(highScoreText), "High Score: %d", highScore);

    UILabelInit(&scoreLabel, scoreText, (Vector2){20, 20}, 20, WHITE);
    UILabelInit(&highScoreLabel, highScoreText, (Vector2){0, 0}, 20, WHITE);
    highScoreLabel.position = (Vector2){SCREEN_WIDTH - UILabelMeasure(&highScoreLabel).x - 20, 20};

    is_paused = false;
    is_gameplay = true;

    FadeStart(&gameplayFade, FADE_IN, 1.0f, BLACK);
    AudioFadeStart(&musicFade, AUDIO_FADE_IN, 1.0f, 0.0f, GetMusicVolume());
    PlayMusicStream(songMusic);
}

void GameplayUpdate() {
    FadeUpdate(&gameplayFade);
    AudioFadeUpdate(&musicFade);

    if (gameplayFade.active) return;

    if (!is_paused) {
    } else PauseUpdate();

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
}
void GameplayDrawing() {
    ClearBackground(BLACK);
    
    UILabelDraw(&scoreLabel);
    UILabelDraw(&highScoreLabel);

    DrawLine(0, 50, SCREEN_WIDTH, 50, WHITE);

    FadeDraw(&gameplayFade);

    if (is_paused) PauseDrawing();
}

void GameplayDeinit() { 
    is_gameplay = false;
    is_paused = false;
    StopMusicStream(songMusic);
}
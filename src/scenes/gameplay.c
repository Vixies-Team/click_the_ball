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
#include "../entities/ball.h"
#include "../utils/utils.h"
#include "../ui/label.h"
#include "../effects/fade.h"

#include "../scenes/pause.h"

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

void GameplayInit() {
    score = 0;

    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    snprintf(highScoreText, sizeof(highScoreText), "High Score: %d", highScore);

    UILabelInit(&scoreLabel, scoreText, (Vector2){20, 20}, 20, WHITE);
    UILabelInit(&highScoreLabel, highScoreText, (Vector2){0, 0}, 20, WHITE);
    highScoreLabel.position = (Vector2){SCREEN_WIDTH - UILabelMeasure(&highScoreLabel).x - 20, 20};

    is_paused = false;
    is_gameplay = true;

    FadeStart(&gameplayFade, FADE_IN, 1.0f, BLACK);

    /*balls = (Ball*)malloc(5 * sizeof(Ball));
    memset(balls, 0, 5 * sizeof(Ball));

    for (int a = 0; a < 5; a++) {
        Vector2 ballPos;
        bool isBallPosValid = true;

        do {
            isBallPosValid = true;

            ballPos = (Vector2){
                (float)GetRandomValue(25, SCREEN_WIDTH - 25),
                (float)GetRandomValue(75, SCREEN_HEIGHT - 25)
            };

            for (int b = 0; b < a; b++) {
                float dx = ballPos.x - balls[b].position.x;
                float dy = ballPos.y - balls[b].position.y;

                float distanceSq = dx * dx + dy * dy;
                float minDistance = 25 + balls[b].radius;

                if (distanceSq < minDistance * minDistance) {
                    isBallPosValid = false;
                    break;
                }
            }
        } while(!isBallPosValid);

        BallInit(&balls[a], ballPos, 25, RED);
        balls[a].velocity = (Vector2){ GetRandomFloat(-10.0f, 10.0f), GetRandomFloat(-10.0f, 10.0f) };
    }*/
}

void GameplayUpdate() {
    FadeUpdate(&gameplayFade);
    if (gameplayFade.active) return;

    if (!is_paused) {
        /*for (int a = 0; a < BALL_COUNT; a++) {
            if (balls[a].position.y - balls[a].radius <= 50) {
                balls[a].velocity.y = fabsf(balls[a].velocity.y);
            }
            else if (balls[a].position.y + balls[a].radius >= SCREEN_HEIGHT) {
                balls[a].velocity.y = -fabsf(balls[a].velocity.y);
            }

            if (balls[a].position.x - balls[a].radius <= 0) {
                balls[a].velocity.x = fabs(balls[a].velocity.x);
            }
            else if (balls[a].position.x + balls[a].radius >= SCREEN_WIDTH) {
                balls[a].velocity.x = -fabsf(balls[a].velocity.x);
            }

            for (int i = 0; i < BALL_COUNT; i++) {
                for (int j = i + 1; j < BALL_COUNT; j++) {
                    if (BallIsColliding(&balls[i], &balls[j])) BallBounce(&balls[i], &balls[j]);
                }
            }

            switch(BallUpdate(&balls[a])) {
                case BALL_EVENT_CLICKED: {
                    PlaySound(shootSfx);
                    score++;
                    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
                    break;
                }
                case BALL_EVENT_NONE: {
                    break;
                }
            }

            WindowUpdate();
        }*/
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
}
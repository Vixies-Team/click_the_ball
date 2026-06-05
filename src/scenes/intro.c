#include <stdio.h>
#include <string.h>

#include "../../vendor/raylib/include/raylib.h"

#include "intro.h"

#include "../core/config.h"
#include "../core/game.h"

#include "../ui/label.h"

#include "../effects/fade.h"

static const char *title = "Vixies Studio";

static int textLength = 13;

static int visibleChars = 0;
static int frameCounter = 0;

static int waitTimer = 0;

static fade introFade;

static UILabel titleLabel;
static UILabel presentLabel;

void IntroInit() {
    FadeInit(&introFade);
    
    UILabelInit(&titleLabel, title, (Vector2){0}, 50, WHITE);
    UILabelInit(&presentLabel, "Present", (Vector2){0}, 25, (Color){180, 180, 180, 0});
    
    titleLabel.position = (Vector2){(SCREEN_WIDTH / 2) - (UILabelMeasure(&titleLabel).x / 2), (SCREEN_HEIGHT / 2) - 30};
    presentLabel.position = (Vector2){(SCREEN_WIDTH / 2) - (UILabelMeasure(&presentLabel).x / 2), (SCREEN_HEIGHT / 2) + 35};
    titleLabel.text = "";
    presentLabel.alpha = 0.0f;
}

void IntroUpdate() {
    frameCounter++;

    if (IsKeyPressed(KEY_ENTER) && !introFade.active) FadeStart(&introFade, FADE_OUT, 1.0f, BLACK);

    if (frameCounter >= 10) {
        frameCounter = 0;
        if (visibleChars < textLength) {
            visibleChars++;
            titleLabel.text = TextSubtext(title, 0, visibleChars);
        }
    }

    if (visibleChars >= textLength) {
        if (presentLabel.alpha <= 1.0f) presentLabel.alpha += 0.02f;
        else {
            if (waitTimer >= 180) {
                if (!introFade.active) FadeStart(&introFade, FADE_OUT, 1.0f, BLACK);
            }
            else waitTimer++;
        }
    }

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
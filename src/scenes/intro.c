#include <stdio.h>
#include <string.h>

#include "../../vendor/raylib/include/raylib.h"

#include "intro.h"
#include "../core/config.h"
#include "../core/game.h"

static const char *title = "Vixies Studio";
static const char *present = "Present";

static int titleFontSize = 50;
static int presentFontSize = 25;

static int textLength = 13;

static int visibleChars = 0;
static int frameCounter = 0;

static int presentAlpha = 0;
static float fadeAlpha = 0.0f;

static int waitTimer = 0;
static bool startFadeOut = false;

static bool is_done = false;

void IntroInit() {
}

void IntroUpdate() {
    frameCounter++;

    if (IsKeyPressed(KEY_ENTER)) {
        startFadeOut = true;
    }

    if (frameCounter >= 10) {
        frameCounter = 0;
        if (visibleChars < textLength) visibleChars++;
    }

    if (visibleChars >= textLength) {
        if (presentAlpha < 255) {
            presentAlpha += 3;
        }
        else {
            waitTimer++;
            if (waitTimer >= 180) startFadeOut = true;
        }
    }

    if (startFadeOut) fadeAlpha += 0.02;
    if (fadeAlpha >= 1.0f) is_done = true;
}
void IntroDrawing() {
    ClearBackground(BLACK);

    DrawText(
        TextSubtext(title, 0, visibleChars),
        (SCREEN_WIDTH / 2) - (MeasureText(title, titleFontSize) / 2),
        (SCREEN_HEIGHT / 2) - 30,
        titleFontSize,
        (Color){255, 255, 255, 255}
    );

    if (visibleChars >= textLength) {
        DrawText(
            present,
            (SCREEN_WIDTH / 2) - (MeasureText(present, presentFontSize) / 2),
            (SCREEN_HEIGHT / 2) + 35,
            presentFontSize,
            (Color){180, 180, 180, presentAlpha}
        );
    }

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, fadeAlpha));
    if (is_done) ChangeScene(SCENE_MENU);
}

void IntroDeinit() {

}
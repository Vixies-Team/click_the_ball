#include <stdio.h>
#include "window.h"

#include "../core/config.h"

static bool shaking = false;
static Vector2 originalPosition;

static float shakeIntensity = 0.0f;
static float shakeTimer = 0.0f;

void WindowInit(int width, int height, const char *title) {
    InitWindow(width, height, title);
}

void WindowShake(float intensity, float duration) {
    if (!shaking) originalPosition = GetWindowPosition();

    shaking = true;
    shakeIntensity = intensity;
    shakeTimer = duration;
}

void WindowUpdate() {
    if (shaking) {
        shakeTimer -= GetFrameTime();

        if (shakeTimer <= 0.0f) {
            SetWindowPosition((int)originalPosition.x, (int)originalPosition.y);
            shaking = false;
            return;
        }

        int offsetX = GetRandomValue(-(int)shakeIntensity, (int)shakeIntensity);
        int offsetY = GetRandomValue(-(int)shakeIntensity, (int)shakeIntensity);

        SetWindowPosition((int)originalPosition.x + offsetX, (int)originalPosition.y + offsetY);
    }
}

void WindowDeinit() {
    CloseWindow();
}
#include <stdio.h>
#include <string.h>

#include "fade.h"

void FadeInit(fade* fades) {
    *fades = (fade){0};
}

void FadeStart(fade* fade, fadeMode mode, float duration, Color color) {
    fade->mode = mode;
    fade->duration = duration;
    fade->timer = 0.0f;
    fade->active = true;
    fade->alpha = (mode == FADE_IN) ? 1.0f : 0.0f;
    fade->color = color;
}

fadeEvent FadeUpdate(fade* fade) {
    if (!fade->active) return FADE_EVENT_NONE;

    fade->timer += GetFrameTime();
    float progress = fade->timer / fade->duration;

    if (progress > 1.0f) progress = 1.0f;
    if (fade->mode == FADE_IN) fade->alpha = 1.0f - progress;
    else fade->alpha = progress;

    if (progress >= 1.0f) {
        fade->active = false;
        return FADE_EVENT_FINISHED;
    }
    return FADE_EVENT_NONE;
}

void FadeDraw(fade* fade) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(fade->color, fade->alpha));
}
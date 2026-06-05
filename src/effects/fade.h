#ifndef FADE_H
#define FADE_H

#include "../../vendor/raylib/include/raylib.h"

typedef enum {
    FADE_NONE,
    FADE_IN,
    FADE_OUT
} fadeMode;

typedef enum {
    FADE_EVENT_NONE,
    FADE_EVENT_FINISHED
} fadeEvent;

typedef struct {
    float alpha;
    float duration;
    float timer;
    fadeMode mode;
    bool active;
    Color color;
} fade;

void FadeInit(fade* fades);
void FadeStart(fade* fade, fadeMode mode, float duration, Color color);
fadeEvent FadeUpdate(fade* fade);
void FadeDraw(fade* fade);

#endif
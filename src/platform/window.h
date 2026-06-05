#ifndef WINDOW_H
#define WINDOW_H

#include "../../vendor/raylib/include/raylib.h"

void WindowInit(int width, int height, const char *title);

void WindowShake(float intensity, float duration);

void WindowUpdate();

void WindowDeinit();

#endif // WINDOW_H
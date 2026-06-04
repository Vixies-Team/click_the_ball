#ifndef WINDOW_H
#define WINDOW_H

#include "../../vendor/raylib/include/raylib.h"

void WindowInit(int width, int height, const char *title);

void WindowUpdate();

void WindowDeinit();

#endif // WINDOW_H
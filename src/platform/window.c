#include <stdio.h>
#include "window.h"

#include "../core/config.h"

void WindowInit(int width, int height, const char *title) {
    InitWindow(width, height, title);
}

void WindowUpdate() {

}

void WindowDeinit() {
    CloseWindow();
}
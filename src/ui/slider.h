#ifndef SLIDER_H
#define SLIDER_H

#include "../../vendor/raylib/include/raylib.h"

typedef void (*SliderCallback)(float value);
typedef struct {
    Rectangle rect;

    int min;
    int max;
    int value;

    bool dragging;

    SliderCallback onDrag;
    SliderCallback onReleased;
} Slider;

void SliderUpdate(Slider *slider);
void SliderDraw(Slider *slider);

#endif
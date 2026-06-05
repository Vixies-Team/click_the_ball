#ifndef SLIDER_H
#define SLIDER_H

#include "../../vendor/raylib/include/raylib.h"

typedef enum {
    SLIDER_EVENT_NONE,
    SLIDER_EVENT_CLICKED,
    SLIDER_EVENT_DRAGGED,
    SLIDER_EVENT_RELEASED
} SliderEvent;

typedef void (*SliderCallback)(float value);
typedef struct {
    Rectangle rect;

    int min;
    int max;
    int value;

    bool dragging;
} Slider;

SliderEvent SliderUpdate(Slider *slider);
void SliderDraw(Slider *slider);

#endif
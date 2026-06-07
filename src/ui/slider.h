#ifndef SLIDER_H
#define SLIDER_H

#include "../../vendor/raylib/include/raylib.h"

typedef enum {
    SLIDER_EVENT_NONE,
    SLIDER_EVENT_CLICKED,
    SLIDER_EVENT_DRAGGED,
    SLIDER_EVENT_RELEASED
} UISliderEvent;

typedef void (*UISliderCallback)(float value);
typedef struct {
    Rectangle rect;

    int min;
    int max;
    int value;

    bool dragging;
} UISlider;

UISliderEvent SliderUpdate(UISlider *slider);
void SliderDraw(UISlider *slider);

#endif
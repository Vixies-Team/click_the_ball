#include <stdio.h>

#include "slider.h"

SliderEvent SliderUpdate(Slider *slider) {
    SliderEvent retEvent = SLIDER_EVENT_NONE;
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, slider->rect)) {
        retEvent = SLIDER_EVENT_CLICKED;
        slider->dragging = true;
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && slider->dragging) {
        retEvent = SLIDER_EVENT_RELEASED;
        slider->dragging = false;
    }
    if (slider->dragging) {
        retEvent = SLIDER_EVENT_DRAGGED;
        float percent = (mouse.x - slider->rect.x) / slider->rect.width;
        if (percent < 0) percent = 0;
        if (percent > 1) percent = 1;

        slider->value = slider->min + (int)((slider->max - slider->min) * percent);
    }

    return retEvent;
}

void SliderDraw(Slider *slider) {
    float percent =(float)(slider->value - slider->min) / (slider->max - slider->min);
    DrawRectangleRec(slider->rect, DARKGRAY);
    DrawRectangle(slider->rect.x, slider->rect.y, slider->rect.width * percent, slider->rect.height, GREEN);
    DrawCircle(slider->rect.x + (slider->rect.width * percent), slider->rect.y + slider->rect.height / 2, 12, WHITE);
}
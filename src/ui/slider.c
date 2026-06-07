#include <stdio.h>

#include "slider.h"

UISliderEvent SliderUpdate(UISlider *UISlider) {
    UISliderEvent retEvent = SLIDER_EVENT_NONE;
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, UISlider->rect)) {
        retEvent = SLIDER_EVENT_CLICKED;
        UISlider->dragging = true;
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && UISlider->dragging) {
        retEvent = SLIDER_EVENT_RELEASED;
        UISlider->dragging = false;
    }
    if (UISlider->dragging) {
        retEvent = SLIDER_EVENT_DRAGGED;
        float percent = (mouse.x - UISlider->rect.x) / UISlider->rect.width;
        if (percent < 0) percent = 0;
        if (percent > 1) percent = 1;

        UISlider->value = UISlider->min + (int)((UISlider->max - UISlider->min) * percent);
    }

    return retEvent;
}

void SliderDraw(UISlider *UISlider) {
    float percent =(float)(UISlider->value - UISlider->min) / (UISlider->max - UISlider->min);
    DrawRectangleRec(UISlider->rect, DARKGRAY);
    DrawRectangle(UISlider->rect.x, UISlider->rect.y, UISlider->rect.width * percent, UISlider->rect.height, GREEN);
    DrawCircle(UISlider->rect.x + (UISlider->rect.width * percent), UISlider->rect.y + UISlider->rect.height / 2, 12, WHITE);
}
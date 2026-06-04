#include <stdio.h>

#include "slider.h"

void SliderUpdate(Slider *slider) {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(
            mouse,
            slider->rect
        )) {
            if (slider->onDrag) slider->onDrag(slider->value);
            slider->dragging = true;
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && slider->dragging) {
        if (slider->onReleased) slider->onReleased(slider->value);
        slider->dragging = false;
    }

    if (slider->dragging) {
        float percent =
            (mouse.x - slider->rect.x) /
            slider->rect.width;

        if (percent < 0)
            percent = 0;

        if (percent > 1)
            percent = 1;

        slider->value =
            slider->min +
            (int)((slider->max - slider->min)
            * percent);
    }
}

void SliderDraw(Slider *slider) {
    float percent =
        (float)(slider->value - slider->min) /
        (slider->max - slider->min);

    DrawRectangleRec(
        slider->rect,
        DARKGRAY
    );

    DrawRectangle(
        slider->rect.x,
        slider->rect.y,
        slider->rect.width * percent,
        slider->rect.height,
        GREEN
    );

    DrawCircle(
        slider->rect.x +
        (slider->rect.width * percent),

        slider->rect.y +
        slider->rect.height / 2,

        12,

        WHITE
    );
}
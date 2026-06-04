#include <stdio.h>
#include "label.h"

void UILabelInit(UILabel* label, const char* text, Vector2 position, int fontSize, Color color) {
    label->text = text;
    label->position = position;

    label->fontSize = fontSize;
    label->spacing = fontSize / 10.0f;

    label->scale = 1.0f;
    label->alpha = 1.0f;

    label->color = color;

    label->font = NULL;
}

void UILabelDraw(UILabel* label) {
    if (!label || !label->text) return;
    Color color = Fade(label->color, label->alpha);
    DrawTextEx(
        label->font ? *label->font : GetFontDefault(),
        label->text,
        label->position,
        label->fontSize * label->scale,
        label->spacing,
        color
    );
}

Vector2 UILabelMeasure(UILabel* label) {
    if (!label || !label->text) return (Vector2){0};
    return MeasureTextEx(
        label->font ? *label->font : GetFontDefault(),
        label->text,
        label->fontSize * label->scale,
        label->spacing
    );
}
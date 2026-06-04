#pragma once

#include "../../vendor/raylib/include/raylib.h"

typedef struct {
    const char* text;

    Vector2 position;

    int fontSize;
    float spacing;

    float scale;
    float alpha;

    Color color;

    Font* font;
} UILabel;

void UILabelInit(UILabel* label, const char* text, Vector2 position, int fontSize, Color color);

void UILabelDraw(UILabel* label);

Vector2 UILabelMeasure(UILabel* label);
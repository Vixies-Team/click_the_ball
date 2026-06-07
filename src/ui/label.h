#ifndef LABEL_H
#define LABEL_H

#include "../../vendor/raylib/include/raylib.h"

typedef struct {
    float duration_per_char;
    float elapsed_per_char;

    int text_visible;
    char char_show;

    bool active;
} UILabelSubtext;

typedef enum {
    UI_LABEL_TYPE_NORMAL,
    UI_LABEL_TYPE_SUBTEXT
} UILabelType;

typedef enum {
    UI_LABEL_EVENT_NONE,
    UI_LABEL_EVENT_TYPING,
    UI_LABEL_EVENT_DONE
} UILabelEvent;

typedef struct {
    const char* text;
    int text_len;
    UILabelType type;

    UILabelSubtext subtext;

    Vector2 position;

    int fontSize;
    float spacing;

    float scale;
    float alpha;

    Color color;
    
    Font* font;
} UILabel;

void UILabelInit(UILabel* label, const char* text, UILabelType type, Vector2 position, int fontSize, Color color, float duration_per_char);

UILabelEvent UILabelUpdate(UILabel* label, float deltaTime);
void UILabelDraw(UILabel* label);

Vector2 UILabelMeasure(UILabel* label);

#endif // LABEL_H
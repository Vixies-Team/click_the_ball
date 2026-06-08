#include <stdio.h>
#include <string.h>

#include "label.h"

void UILabelInit(UILabel* label, const char* text, UILabelType type, Vector2 position, int fontSize, Color color, float duration_per_char) {
    *label = (UILabel){0}; // ini buat ngeset memory zero

    label->text = text; // ini text nya,
    label->text_len = strlen(text); // buat length nya
    label->type = type; // buat type labelnya, bahwa ini type normal atau subtext
    label->subtext = (UILabelSubtext){0}; // ini kalo orang pake subtext

    label->position = position; // ini posisi nya (pake vector2)

    label->fontSize = fontSize; // ini fontsize nya
    label->spacing = fontSize / 10.0f; // ini spacing font nya

    label->scale = 1.0f; // skala buat font size nya
    label->alpha = 1.0f; // ini buat kek macam transparent font.

    label->color = color; // ini buat color text nya

    label->font = NULL; // ini buat custom font kalo lu mau pake

    if (label->type == UI_LABEL_TYPE_SUBTEXT) {
        label->subtext.duration_per_char = duration_per_char;
        label->subtext.active = true;
    }
}

UILabelEvent UILabelUpdate(UILabel* label, float deltaTime) {
    if (!label) return UI_LABEL_EVENT_NONE;

    switch(label->type) {
        case UI_LABEL_TYPE_NORMAL: break;
        case UI_LABEL_TYPE_SUBTEXT: {
            if (!label->subtext.active) return UI_LABEL_EVENT_NONE;
            label->subtext.elapsed_per_char += deltaTime;
            if (label->subtext.elapsed_per_char > label->subtext.duration_per_char) {
                if (label->subtext.text_visible >= label->text_len) {
                    label->subtext.active = false;
                    return UI_LABEL_EVENT_DONE;
                }
                label->subtext.char_show = *(label->text + label->subtext.text_visible);
                label->subtext.text_visible++;
                label->subtext.elapsed_per_char = 0.0f;
                return UI_LABEL_EVENT_TYPING;
            }
        }
    }

    return UI_LABEL_EVENT_NONE;
}

void UILabelDraw(UILabel* label) {
    if (!label || !label->text) return;
    
    DrawTextEx(
        label->font ? *label->font : GetFontDefault(),
        label->type == UI_LABEL_TYPE_NORMAL ? label->text : TextSubtext(label->text, 0, label->subtext.text_visible),
        label->position,
        label->fontSize * label->scale,
        label->spacing,
        Fade(label->color, label->alpha)
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
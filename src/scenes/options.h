#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
    int music;
    int sfx;
} OptionsMenu;

void OptionsInit();

void OptionsUpdate();
void OptionsDrawing();

void OptionsDeinit();

#endif // OPTIONS_H
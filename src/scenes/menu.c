#include <stdio.h>
#include "../../vendor/raylib/include/raylib.h"

#include "menu.h"

#include "../core/config.h"
#include "../core/game.h"
#include "../core/scene.h"
#include "../audio/audio.h"

#include "../ui/label.h"

#include "../effects/fade.h"

#include "gameplay.h"

#define MENU_SIZE 3

static int selected = 0;
static const char *menuItems[] = {
    "Start Game",
    "Options",
    "Exit"
};

static fade menuFade;

static UILabel menuLabel[MENU_SIZE];
static UILabel gameTitleLabel;
static UILabel hintLabel;
static UILabel copyrightLabel;
static UILabel versionlabel;

void MenuInit() {
    UILabelInit(&gameTitleLabel, GAME_TITLE, (Vector2){0}, 40, WHITE);
    gameTitleLabel.position = (Vector2){SCREEN_WIDTH/2 - UILabelMeasure(&gameTitleLabel).x / 2, 80};

    UILabelInit(&hintLabel, "Use Arrow Keys + ENTER", (Vector2){0}, 20, WHITE);
    hintLabel.position = (Vector2){SCREEN_WIDTH/2 - UILabelMeasure(&hintLabel).x / 2, 350};
    
    UILabelInit(&copyrightLabel, "© 2026 Vixies Studio", (Vector2){10, SCREEN_HEIGHT - 35}, 24, GRAY);
    UILabelInit(&versionlabel, "Version 0.1", (Vector2){0}, 24, GRAY);
    versionlabel.position = (Vector2){SCREEN_WIDTH - UILabelMeasure(&versionlabel).x - 10, SCREEN_HEIGHT - 35};

    for (int a = 0; a < MENU_SIZE; a++) {
        UILabelInit(&menuLabel[a], menuItems[a], (Vector2){0}, 30, GRAY);
        menuLabel[a].position = (Vector2){SCREEN_WIDTH/2 - UILabelMeasure(&menuLabel[a]).x / 2, 180 + (a * 50)};
    }

    FadeStart(&menuFade, FADE_IN, 1.0f, BLACK);
}

void MenuUpdate() {
    if (!menuFade.active) {
        if (IsKeyPressed(KEY_DOWN)) {
            selected++;
            if (selected >= MENU_SIZE) selected = 0;
            PlaySound(menuSfx);
        }
        else if (IsKeyPressed(KEY_UP)) {
            selected--;
            if (selected < 0) selected = MENU_SIZE - 1;
            PlaySound(menuSfx);
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            PlaySound(selectSfx);
            switch(selected) {
                case 0: {
                    GameplayInit();
                    FadeStart(&menuFade, FADE_OUT, 1.0f, BLACK);
                    break;
                }   
                case 1: {
                    ChangeScene(SCENE_OPTIONS);
                    break;
                }
                case 2: {
                    FadeStart(&menuFade, FADE_OUT, 1.0f, BLACK);
                    break;
                }
            }
        }
    }
    
    if (FadeUpdate(&menuFade) == FADE_EVENT_FINISHED && menuFade.mode == FADE_OUT) {
        if (selected == 0) ChangeScene(SCENE_GAMEPLAY);
        else if (selected == 2) running = false;
    }
}
void MenuDrawing() {
    ClearBackground(BLACK);

    UILabelDraw(&gameTitleLabel);

    for (int a = 0; a < MENU_SIZE; a++) {
        menuLabel[a].color = a == selected ? YELLOW : GRAY;
        UILabelDraw(&menuLabel[a]);
    }

    UILabelDraw(&hintLabel);
    UILabelDraw(&copyrightLabel);
    UILabelDraw(&versionlabel);

    FadeDraw(&menuFade);
}

void MenuDeinit() {
    
}
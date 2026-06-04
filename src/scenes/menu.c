#include <stdio.h>
#include "../../vendor/raylib/include/raylib.h"

#include "menu.h"

#include "../core/config.h"
#include "../core/game.h"
#include "../core/scene.h"
#include "../audio/audio.h"

#include "../ui/label.h"

#include "gameplay.h"

#define MENU_SIZE 3

static float fadeAlpha = 1.0f;
static bool is_exit = false;
static bool is_beginning = true;

static int selected = 0;
static const char *menuItems[] = {
    "Start Game",
    "Options",
    "Exit"
};

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
}

void MenuUpdate() {
    if (is_beginning) {
        if (fadeAlpha <= 0.0f) is_beginning = false;
        else fadeAlpha -= 0.02f;
    }
    else if (is_exit) {
        if (fadeAlpha >= 1.0f) running = false;
        else fadeAlpha += 0.02f;
    }
    else {
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
                    ChangeScene(SCENE_GAMEPLAY);
                    break;
                }   
                case 1: {
                    ChangeScene(SCENE_OPTIONS);
                    break;
                }
                case 2: {
                    is_exit = true;
                    break;
                }
            }
        }
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
    
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, fadeAlpha)); // ini buat fade in/out
}

void MenuDeinit() {
    
}
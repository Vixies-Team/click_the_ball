#include <stdio.h>
#include "../../vendor/raylib/include/raylib.h"

#include "game.h"
#include "scene.h"
#include "config.h"

#include "../audio/audio.h"
#include "../scenes/intro.h"
#include "../scenes/menu.h"
#include "../scenes/gameplay.h"
#include "../scenes/options.h"

#include "../platform/window.h"

#include "../assets/assets.h"

Scene currentScene = SCENE_INTRO;
bool running = true;

void GameInit() {
    SetTraceLogLevel(LOG_NONE);

    WindowInit(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(TARGET_FPS);
    SetExitKey(KEY_NULL);

    AssetsInit("data.vxpck");
    AudioInit();
    IntroInit();
    MenuInit();
    OptionsInit();
}

void GameUpdate() {
    AudioUpdate();

    switch(currentScene) {
        case SCENE_INTRO: {
            IntroUpdate();
            break;
        }
        case SCENE_MENU: {
            MenuUpdate();
            break;
        }
        case SCENE_GAMEPLAY: {
            GameplayUpdate();
            break;
        }
        case SCENE_OPTIONS: {
            OptionsUpdate();
            break;
        }
    }

    if (WindowShouldClose()) running = false;
}

void GameDrawing() {
    BeginDrawing();
        switch(currentScene) {
            case SCENE_INTRO: {
                IntroDrawing();
                break;
            }
            case SCENE_MENU: {
                MenuDrawing();
                break;
            }
            case SCENE_GAMEPLAY: {
                GameplayDrawing();
                break;
            }
            case SCENE_OPTIONS: {
                OptionsDrawing();
                break;
            }
        }
    EndDrawing();
}

void ChangeScene(Scene scene) {
    currentScene = scene;
}

void GameDeinit() {
    AudioDeinit();
    IntroDeinit();
    MenuDeinit();
    OptionsDeinit();
    WindowDeinit();
}
#include <stdio.h>
#include "../vendor/raylib/include/raylib.h"

#include "core/config.h"
#include "core/scene.h"
#include "core/game.h"

int main() {
    GameInit();

    while(running) {
        GameUpdate();
        GameDrawing();
    }

    GameDeinit();
    return 0;
}
#ifndef GAME_H
#define GAME_H

#include "scene.h"

extern bool running;

void GameInit();

void GameUpdate();
void GameDrawing();
void ChangeScene(Scene scene);


void GameDeinit();

#endif // GAME_H
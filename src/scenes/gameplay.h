#ifndef GAMEPLAY_H
#define GAMEPLAY_H

extern bool is_paused;
extern bool is_gameplay;

void GameplayInit();

void GameplayUpdate();
void GameplayDrawing();

void GameplayDeinit();

#endif // GAMEPLAY_H
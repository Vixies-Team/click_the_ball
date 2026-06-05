#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../audio/audio_fade.h"

extern bool is_paused;
extern bool is_gameplay;

extern AudioFade musicFade;

void GameplayInit();

void GameplayUpdate();
void GameplayDrawing();

void GameplayDeinit();

#endif // GAMEPLAY_H
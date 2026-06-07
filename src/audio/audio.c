#include <stdio.h>
#include "../../vendor/raylib/include/raylib.h"

#include "audio.h"

#include "../assets/assets.h"

Sound selectSfx;
Sound menuSfx;
Sound shootSfx;
Sound talkingSfx;

static uint32_t songBufferSize;
static void* songBuffer;
Music songMusic;

void AudioInit() {
    InitAudioDevice();

    selectSfx = Assets_LoadSound("sfx/select.wav");
    menuSfx = Assets_LoadSound("sfx/menu.wav");
    shootSfx = Assets_LoadSound("sfx/shoot.wav");
    talkingSfx = Assets_LoadSound("sfx/talking.wav");

    songBuffer = Assets_LoadFile("music/killer_trip.ogg", &songBufferSize);
    songMusic = LoadMusicStreamFromMemory(GetFileExtension("music/killer_trip.ogg"), songBuffer, songBufferSize);
}

void AudioUpdate() {
    UpdateMusicStream(songMusic);
}

void AudioDeinit() {
    UnloadSound(selectSfx);
    UnloadSound(menuSfx);
    UnloadSound(shootSfx);
    UnloadSound(talkingSfx);

    UnloadMusicStream(songMusic);

    free(songBuffer);
    CloseAudioDevice();
}
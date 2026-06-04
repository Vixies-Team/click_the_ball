#include <stdio.h>
#include "../../vendor/raylib/include/raylib.h"

#include "audio.h"

#include "../assets/assets.h"

Sound selectSfx;
Sound menuSfx;
Sound shootSfx;

void AudioInit() {
    InitAudioDevice();

    selectSfx = Assets_LoadAudio("sfx/select.wav");
    menuSfx = Assets_LoadAudio("sfx/menu.wav");
    shootSfx = Assets_LoadAudio("sfx/shoot.wav");
}

void AudioUpdate() {

}

void AudioDeinit() {
    UnloadSound(selectSfx);
    UnloadSound(menuSfx);
}

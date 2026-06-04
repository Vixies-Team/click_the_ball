#ifndef AUDIO_H
#define AUDIO_H

extern Sound selectSfx;
extern Sound menuSfx;
extern Sound shootSfx;

void AudioInit();
void AudioUpdate();
void AudioDeinit();

#endif // AUDIO_H
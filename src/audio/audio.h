#ifndef AUDIO_H
#define AUDIO_H

extern Sound selectSfx;
extern Sound menuSfx;
extern Sound shootSfx;
extern Sound talkingSfx;

extern Music songMusic;

void AudioInit();
void AudioUpdate();
void AudioDeinit();

#endif // AUDIO_H
#ifndef AUDIO_FADE_H
#define AUDIO_FADE_H

#include "../../vendor/raylib/include/raylib.h"

typedef enum {
    AUDIO_FADE_NONE,
    AUDIO_FADE_IN,
    AUDIO_FADE_OUT
} AudioFadeMode;

typedef enum {
    AUDIO_TYPE_MUSIC,
    AUDIO_TYPE_SOUND,
} AudioFadeType;

typedef enum {
    AUDIO_FADE_EVENT_NONE,
    AUDIO_FADE_EVENT_FINISHED
} AudioFadeEvent;

typedef struct {
    AudioFadeMode mode;
    AudioFadeType type;
    void* audio_ptr;

    float duration;
    float timer;

    float startVolume;
    float targetVolume;
    float currentVolume;

    bool active;
} AudioFade;

void AudioFadeInit(AudioFade* audioFade, AudioFadeType type, void* audio_ptr);

void AudioFadeStart(AudioFade* audioFade, AudioFadeMode mode, float duration, float startVolume, float targetVolume);

AudioFadeEvent AudioFadeUpdate(AudioFade* audioFade);

#endif // AUDIO_FADE_H
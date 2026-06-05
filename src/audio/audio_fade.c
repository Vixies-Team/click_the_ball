#include <stdio.h>

#include "audio_fade.h"

void AudioFadeInit(AudioFade* audioFade, AudioFadeType type, void* audio_ptr) {
    *audioFade = (AudioFade){0};
    audioFade->type = type;
    audioFade->audio_ptr = audio_ptr;
}

void AudioFadeStart(AudioFade* audioFade, AudioFadeMode mode, float duration, float startVolume, float targetVolume) {
    audioFade->mode = mode;
    audioFade->duration = duration;
    audioFade->timer = 0.0f;

    audioFade->startVolume = startVolume;
    audioFade->targetVolume = targetVolume;
    audioFade->currentVolume = startVolume;

    audioFade->active = true;
}

AudioFadeEvent AudioFadeUpdate(AudioFade* audioFade) {
    if (!audioFade->active) return AUDIO_FADE_EVENT_NONE;

    audioFade->timer += GetFrameTime();

    float progress = audioFade->timer / audioFade->duration;
    if (progress > 1.0f) progress = 1.0f;

    if (audioFade->mode == AUDIO_FADE_IN) {
        audioFade->currentVolume = audioFade->targetVolume * progress;
    }
    else if (audioFade->mode == AUDIO_FADE_OUT) {
        audioFade->currentVolume = audioFade->startVolume * (1.0f - progress);
    }

    if (audioFade->currentVolume < 0.0f) audioFade->currentVolume = 0.0f;
    if (audioFade->currentVolume > 1.0f) audioFade->currentVolume = 1.0f;
    
    if (audioFade->type == AUDIO_TYPE_MUSIC) SetMusicVolume(*(Music*)audioFade->audio_ptr, audioFade->currentVolume);
    else if (audioFade->type == AUDIO_TYPE_SOUND) SetSoundVolume(*(Sound*)audioFade->audio_ptr, audioFade->currentVolume);
    
    if (progress >= 1.0f) {
        audioFade->active = false;
        audioFade->currentVolume = (audioFade->mode == AUDIO_FADE_IN) ? audioFade->targetVolume : 0.0f;
        return AUDIO_FADE_EVENT_FINISHED;
    }

    return AUDIO_FADE_EVENT_NONE;
}
#include "timer.h"

void TimerInit(Timer* timer, float duration) {
    *timer = (Timer){0};

    timer->duration = duration;
}

void TimerReset(Timer* timer) {
    timer->elapsed = 0.0f;
}

void TimerStop(Timer* timer) {
    timer->active = false;
}

void TimerStart(Timer* timer) {
    timer->active = true;
}

TimerEvent TimerUpdate(Timer* timer, float deltaTime) {
    if (!timer->active) return TIMER_EVENT_NONE;

    timer->elapsed += deltaTime;
    
    if (timer->elapsed >= timer->duration) {
        timer->elapsed = timer->duration;
        timer->active = false;

        return TIMER_EVENT_FINISHED;
    } else return TIMER_EVENT_RUNNING;
    return TIMER_EVENT_NONE;
}
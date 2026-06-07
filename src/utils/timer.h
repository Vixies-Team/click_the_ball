#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    float duration;
    float elapsed;
    bool active;
} Timer;

typedef enum {
    TIMER_EVENT_NONE,
    TIMER_EVENT_RUNNING,
    TIMER_EVENT_FINISHED
} TimerEvent;

void TimerInit(Timer* timer, float duration);

void TimerReset(Timer* timer);
void TimerStop(Timer* timer);
void TimerStart(Timer* timer);

TimerEvent TimerUpdate(Timer* timer, float deltaTime);

#endif // TIMER_H
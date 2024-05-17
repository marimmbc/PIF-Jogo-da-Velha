#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdbool.h>
#include <sys/time.h>

typedef struct {
    struct timeval start_time;
    int interval;
    bool running;
} Timer;

void timerInit(Timer *timer, int valueMilliSec);

void timerDestroy(Timer *timer);

void timerUpdateInterval(Timer *timer, int valueMilliSec);

int timerTimeOver(Timer *timer);

void timerPrint(const Timer *timer);

void timerSetCallback(Timer *timer, void (*callback)(void));

void timerStart(Timer *timer);

void timerStop(Timer *timer);

#endif 

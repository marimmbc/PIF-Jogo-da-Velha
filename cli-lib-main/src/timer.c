#include "timer.h"
#include <stdio.h>

void timerInit(Timer *timer, int valueMilliSec)
{
    gettimeofday(&timer->start_time, NULL);
    timer->interval = valueMilliSec;
    timer->running = true;
}

void timerDestroy(Timer *timer)
{
}

void timerUpdateInterval(Timer *timer, int valueMilliSec)
{
    timer->interval = valueMilliSec;
}

int timerTimeOver(Timer *timer)
{
    if (!timer->running)
        return 0;

    struct timeval now, diff;
    gettimeofday(&now, NULL);
    timersub(&now, &timer->start_time, &diff);
    int elapsed = diff.tv_sec * 1000 + diff.tv_usec / 1000;

    return elapsed >= timer->interval;
}

void timerPrint(const Timer *timer)
{
    printf("Timer running: %s, Interval: %d ms\n", timer->running ? "Yes" : "No", timer->interval);
}

void timerStart(Timer *timer)
{
    gettimeofday(&timer->start_time, NULL);
    timer->running = true;
}

void timerStop(Timer *timer)
{
    timer->running = false;
}
#ifndef _TIMER_H
#define _TIMER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

extern timer_t toStandby;
extern timer_t toIdle;

int createTimer(timer_t *timer, void (*handle)(union sigval v));
int startTimer(timer_t *timer, time_t sec);
int stopTimer(timer_t *timer);
int destroyTimer(timer_t *timer);

#endif


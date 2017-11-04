#ifndef _LIBG_TIMER_H
#define _LIBG_TIMER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

int createTimer(timer_t *timer, void (*handle)(union sigval v));
int startTimer(timer_t *timer, time_t sec);
int stopTimer(timer_t *timer);
int destroyTimer(timer_t *timer);

#endif


#include "libg_timer.h"
#include "libg_log.h"

int createTimer(timer_t *timer, void (*handle)(union sigval v))
{
	struct sigevent evp;
	int ret;

	memset (&evp, 0, sizeof (evp));
	evp.sigev_value.sival_ptr = timer;
	evp.sigev_notify = SIGEV_THREAD;
	evp.sigev_notify_function = handle;

    ret = timer_create(CLOCK_MONOTONIC, &evp, timer);
    if(ret)
        perror("timer_create");

	return 0;
}

int startTimer(timer_t *timer, time_t sec)
{
    struct itimerspec ts;
    int ret;

    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = sec;
    ts.it_value.tv_nsec = 0;

    ret = timer_settime(*timer, 0, &ts, NULL);
    if(ret)
        perror("timer_settime");
	return 0;
}

int stopTimer(timer_t *timer)
{
    struct itimerspec ts;
    int ret;

    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = 0;
    ts.it_value.tv_nsec = 0;

    ret = timer_settime(*timer, 0, &ts, NULL);
    if(ret)
        perror("timer_settime");
	return 0;
}

int destroyTimer(timer_t *timer)
{
	timer_delete(*timer);
	return 0;
}


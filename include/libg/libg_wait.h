#ifndef _LIBG_WAIT_H
#define _LIBG_WAIT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct libg_wait
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

typedef bool vjudge(va_list arg);

void libg_wait_init(struct libg_wait *wait);
void libg_wait_cond(struct libg_wait *wait, vjudge *judge, ...);
void libg_wait_trigger(struct libg_wait *wait);

#ifdef __cplusplus
}
#endif

#endif



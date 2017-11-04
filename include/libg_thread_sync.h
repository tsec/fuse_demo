#ifndef _LIBG_THREAD_SYNC_H
#define _LIBG_THREAD_SYNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#ifdef __cplusplus
extern "C"
{
#endif

struct libg_thread_sync
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int cnt;
};

int libg_thread_sync_init(struct libg_thread_sync *sync, int cnt);
int libg_thread_sync_wait(struct libg_thread_sync *sync);
int libg_thread_sync_destory(struct libg_thread_sync *sync);

#ifdef __cplusplus
}
#endif

#endif


#ifndef _THREAD_SYNC_H_
#define _THREAD_SYNC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_sync
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nCnt;
};

int sync_init(struct thread_sync *sync, int nCnt);

int sync_wait(struct thread_sync *sync);

int sync_destory(struct thread_sync *sync);

#endif


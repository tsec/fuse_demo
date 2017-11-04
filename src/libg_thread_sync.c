#include "thread_sync.h"

int sync_init(struct thread_sync *sync, int nCnt)
{
	pthread_mutex_init(&(sync->mutex), NULL);
	pthread_cond_init(&(sync->cond), NULL);
	sync->nCnt = nCnt;
	return 0;
}

int sync_wait(struct thread_sync *sync)
{
	pthread_mutex_lock(&(sync->mutex));
	sync->nCnt--;
	
	if(sync->nCnt != 0)
	{
		pthread_cond_wait(&(sync->cond), &(sync->mutex));
	}
	else
	{
		pthread_cond_broadcast(&(sync->cond));
	}
	pthread_mutex_unlock(&(sync->mutex));
	return 0;
}

int sync_destory(struct thread_sync *sync)
{
	pthread_mutex_destroy(&(sync->mutex)); 
	pthread_cond_destroy(&(sync->cond));
	return 0;
}
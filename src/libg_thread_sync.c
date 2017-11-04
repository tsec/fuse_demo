#include "libg_thread_sync.h"
#include "libg_log.h"

int libg_thread_sync_init(struct libg_thread_sync *sync, int cnt)
{
	pthread_mutex_init(&(sync->mutex), NULL);
	pthread_cond_init(&(sync->cond), NULL);
	sync->cnt = cnt;
	return 0;
}

int libg_thread_sync_wait(struct libg_thread_sync *sync)
{
	pthread_mutex_lock(&(sync->mutex));
	sync->cnt--;
	
	if(sync->cnt != 0)
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

int libg_thread_sync_destory(struct libg_thread_sync *sync)
{
	pthread_mutex_destroy(&(sync->mutex)); 
	pthread_cond_destroy(&(sync->cond));
	return 0;
}
#include "libg/libg_wait.h"

void libg_wait_init(struct libg_wait *wait)
{
	pthread_mutex_init(&(wait->mutex), NULL);
	pthread_cond_init(&(wait->cond), NULL);
}

void libg_wait_cond(struct libg_wait *wait, vjudge *judge, ...)
{
	pthread_mutex_lock(&(wait->mutex));
    va_list arg;
    va_start(arg, judge);
    while(true)
    {
		if(judge(arg))
		{
			break;
		}
		else
		{
			pthread_cond_wait(&(wait->cond), &(wait->mutex));
		}
    }
    va_end(arg);
    pthread_mutex_unlock(&(wait->mutex));
}


void libg_wait_trigger(struct libg_wait *wait)
{
	pthread_mutex_lock(&(wait->mutex));
	pthread_cond_broadcast(&(wait->cond));
	pthread_mutex_unlock(&(wait->mutex));
}


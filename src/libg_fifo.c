#include "libg/libg_fifo.h"
#include "libg/libg_log.h"
/*
 * internal helper to calculate the unused elements in a fifo
 */
static inline unsigned int gfifo_unused(struct gfifo *fifo)
{
	return (fifo->mask + 1) - (fifo->in - fifo->out);
}

static inline unsigned int min(unsigned int a, unsigned int b)
{
	return (a < b) ? a : b;
}

int gfifo_alloc(struct gfifo *fifo, unsigned int size,
		size_t esize)
{
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;

	if (size < 2) {
		fifo->data = NULL;
		fifo->mask = 0;
		return -1;
	}

	fifo->data = malloc(size * esize);

	if (!fifo->data) {
		fifo->mask = 0;
		return -1;
	}
	fifo->mask = size - 1;
	pthread_mutex_init(&(fifo->mutex), NULL);
	return 0;
}


void gfifo_free(struct gfifo *fifo)
{
	pthread_mutex_lock(&(fifo->mutex));
	if(fifo->data != NULL)
	{
		free(fifo->data);
	}
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = 0;
	fifo->data = NULL;
	fifo->mask = 0;
	pthread_mutex_unlock(&(fifo->mutex));
	pthread_mutex_destroy(&(fifo->mutex));
}

void gfifo_reset(struct gfifo *fifo)
{
	pthread_mutex_lock(&(fifo->mutex));
	fifo->in = 0;
	fifo->out = 0;
	pthread_mutex_unlock(&(fifo->mutex));
}

void gfifo_backoff(struct gfifo *fifo, int backoff)
{
	pthread_mutex_lock(&(fifo->mutex));
	fifo->out -= (unsigned int)backoff;
	pthread_mutex_unlock(&(fifo->mutex));
}

int gfifo_init(struct gfifo *fifo, void *buffer,
		unsigned int size, size_t esize)
{
	size /= esize;

	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;
	fifo->data = buffer;

	if (size < 2) {
		fifo->mask = 0;
		return -1;
	}
	fifo->mask = size - 1;
	pthread_mutex_init(&(fifo->mutex), NULL);
	return 0;
}


static void gfifo_copy_in(struct gfifo *fifo, const void *src,
		unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);

	memcpy(fifo->data + off, src, l);
	memcpy(fifo->data, src + l, len - l);
}

unsigned int gfifo_in(struct gfifo *fifo,
		const void *buf, unsigned int len)
{
	unsigned int l;
	pthread_mutex_lock(&(fifo->mutex));
	l = gfifo_unused(fifo);
	if (len > l)
		len = l;

	gfifo_copy_in(fifo, buf, len, fifo->in);
	fifo->in += len;
	pthread_mutex_unlock(&(fifo->mutex));
	return len;
}

static void gfifo_copy_out(struct gfifo *fifo, void *dst,
		unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);

	memcpy(dst, fifo->data + off, l);
	memcpy(dst + l, fifo->data, len - l);

}

unsigned int gfifo_out_peek(struct gfifo *fifo,
		void *buf, unsigned int len)
{
	unsigned int l;

	l = fifo->in - fifo->out;
	if (len > l)
		len = l;

	gfifo_copy_out(fifo, buf, len, fifo->out);
	return len;
}

unsigned int gfifo_out(struct gfifo *fifo,
		void *buf, unsigned int len)
{
	pthread_mutex_lock(&(fifo->mutex));
	len = gfifo_out_peek(fifo, buf, len);
	fifo->out += len;
	pthread_mutex_unlock(&(fifo->mutex));
	return len;
}

unsigned int gfifo_out_block(struct gfifo *fifo,
		void *buf, unsigned int len)
{
	unsigned int l;

	while(true)
	{
		pthread_mutex_lock(&(fifo->mutex));
		l = fifo->in - fifo->out;
		pthread_mutex_unlock(&(fifo->mutex));

		if(l >= len)
		{
			gfifo_out(fifo, buf, len);
			break;
		}
		else
		{
			usleep(10 * 1000);
		}
	}

	return len;
}


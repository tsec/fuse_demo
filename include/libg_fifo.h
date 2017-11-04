#ifndef _GFIFO_H_
#define _GFIFO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
struct gfifo {
	unsigned int	in;
	unsigned int	out;
	unsigned int	mask;
	unsigned int	esize;
	void			*data;
	pthread_mutex_t mutex;
};

int gfifo_alloc(struct gfifo *fifo, unsigned int size, size_t esize);

void gfifo_free(struct gfifo *fifo);

int gfifo_init(struct gfifo *fifo, void *buffer, unsigned int size, size_t esize);

unsigned int gfifo_in(struct gfifo *fifo, const void *buf, unsigned int len);

unsigned int gfifo_out(struct gfifo *fifo, void *buf, unsigned int len);

unsigned int gfifo_out_block(struct gfifo *fifo, void *buf, unsigned int len);

void gfifo_reset(struct gfifo *fifo);

#endif


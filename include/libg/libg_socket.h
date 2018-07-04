#ifndef _LIBG_SOCKET_H
#define _LIBG_SOCKET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

int libg_udp_send(int port, char *buf, int len);
int libg_udp_send_recv(int port, char *data, int len, char *buf, int *size);

int libg_udp_server(int port, int *sockfd, void *(*thread_func) (void *), void *arg);

#ifdef __cplusplus
}
#endif

#endif



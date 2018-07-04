#ifndef _LIBG_MISC_H
#define _LIBG_MISC_H

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

char *get_uuid(char *buf);
char *get_timestamp();

#ifdef __cplusplus
}
#endif

#endif




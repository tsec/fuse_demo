#ifndef _LIBG_H
#define _LIBG_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "libg/libg_fs.h"
#include "libg/libg_log.h"
#include "libg/libg_fifo.h"
#include "libg/libg_file.h"
#include "libg/libg_proc.h"
#include "libg/libg_queue.h"
#include "libg/libg_thread_sync.h"
#include "libg/libg_timer.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define LIBG_ROOT	"/tmp/libg"
typedef void *(*USER_MAIN)(void *arg);

int libg_init();

#ifdef __cplusplus
}
#endif

#endif


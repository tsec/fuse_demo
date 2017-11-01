#ifndef _LIBG_FS_H
#define _LIBG_FS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fuse.h>

#ifdef __cplusplus
extern "C"
{
#endif

int libg_fs_create();
int libg_fs_remove();

#ifdef __cplusplus
}
#endif

#endif



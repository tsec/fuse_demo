#ifndef _LIBG_FS_H
#define _LIBG_FS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fuse.h>
#include <glib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define FS_OK			0
#define FS_DUPLICATE	-1
#define FS_NO_EXIST		-2

struct file_node
{
	char name[64];

    int (*open) (const char *, struct fuse_file_info *);
    int (*read) (const char *, char *, size_t, off_t, struct fuse_file_info *);
    int (*write) (const char *, const char *, size_t, off_t, struct fuse_file_info *);
    int (*size) ();
};

struct file_node *libg_fs_alloc_node();
int libg_fs_create();
int libg_fs_remove();

#ifdef __cplusplus
}
#endif

#endif



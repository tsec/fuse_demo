/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall `pkg-config fuse --cflags --libs` libg.c -o libg

  arm-openwrt-linux-gcc hello_v2.c -o test -I$STAGING_DIR/include -L$STAGING_DIR/lib -lfuse -D_FILE_OFFSET_BITS=64

export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/home/guolicun/work/moorebot/allwinner_develop/tina/staging_dir/toolchain-arm_cortex-a7+neon_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin

export STAGING_DIR=/home/guolicun/work/moorebot/allwinner_develop/tina/staging_dir/target-arm_cortex-a7+neon_uClibc-0.9.33.2_eabi/usr

*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "libg.h"
char libg_str[32] = "libg World!\n";
static const char *libg_path = "/libg";

static int libg_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0666;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, libg_path) == 0) {
		stbuf->st_mode = S_IFREG | 0666;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(libg_str);
	} else
		res = -ENOENT;

	return res;
}

static int libg_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, libg_path + 1, NULL, 0);

	return 0;
}

static int libg_open(const char *path, struct fuse_file_info *fi)
{
	libg_log_info("%s\n", path);

/*	if (strcmp(path, libg_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;
*/
	return 0;
}

static int libg_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	if(strcmp(path, libg_path) != 0)
		return -ENOENT;

	len = strlen(libg_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, libg_str + offset, size);
	} else
		size = 0;

	return size;
}

static int libg_write(const char *path, const char *buf, size_t size,
		      off_t offset, struct fuse_file_info *fi)
{
	(void) buf;
	(void) offset;
	(void) fi;
	memset(libg_str, '\0', sizeof(libg_str));
	memcpy(libg_str, buf, size);

	return size;
}
static struct fuse_operations libg_oper = {
	.getattr	= libg_getattr,
	.readdir	= libg_readdir,
	.open		= libg_open,
	.read		= libg_read,
	.write		= libg_write,
};

int main(int argc, char *argv[])
{
	libg_log_init("libg", LOG_INFO);

	return fuse_main(argc, argv, &libg_oper, NULL);
}

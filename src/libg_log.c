#include <sys/time.h>

#include "libg/libg_fs.h"
#include "libg/libg_log.h"

static char log_buf[32] = {'\0'};

static int libg_log_open(const char *path, struct fuse_file_info *fi)
{
	libg_log_info("%s\n", path);

/*	if (strcmp(path, libg_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;
*/
	return 0;
}

static int libg_log_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	int len = strlen(log_buf);
	libg_log_info("libg_log_read: %s\n", path);
	if(offset < len)
	{
		if (offset + size > len)
		{
			size = len - offset;
		}
		memcpy(buf, log_buf + offset, size);
	}
	else
	{
		size = 0;
	}
	return size;
}

static int libg_log_write(const char *path, const char *buf, size_t size,
		      off_t offset, struct fuse_file_info *fi)
{
	(void) buf;
	(void) offset;
	(void) fi;
	libg_log_info("libg_log_write: %s\n", path);
	memset(log_buf, '\0', sizeof(log_buf));
	memcpy(log_buf, buf, size);

	return size;
}

static int libg_log_size()
{
  return strlen(log_buf);
}

int libg_log_create()
{
	struct file_node *node = libg_fs_alloc_node("log_level");

	node->open	= libg_log_open;
	node->read	= libg_log_read;
	node->write	= libg_log_write;
	node->size	= libg_log_size;
	libg_fs_create(node);
	return 0;
}

char *libg_get_time_stamp()
{
    static char buf[64];
    char tmp[64];
    memset(buf, '\0', sizeof(buf));
    memset(tmp, '\0', sizeof(tmp));
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);

    sprintf(tmp, "%s", ctime(&(tv.tv_sec)));
    tmp[strlen(tmp) - 1] = '\0';

    sprintf(buf, "%s %d", tmp, (int)(tv.tv_usec / 1000));
    return buf;
}


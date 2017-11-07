#include "libg/libg_fs.h"
#include "libg/libg_log.h"

GList *file_list = NULL;
static pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

gint libg_fs_check_duplicate(gconstpointer list_node, gconstpointer new_node)
{
	return strcmp(((struct file_node *)list_node)->name, ((struct file_node *)new_node)->name);
}

struct file_node *libg_fs_alloc_node(char *file_name)
{
	struct file_node *node = (struct file_node *)calloc(1, sizeof(struct file_node));
	if(NULL == node)
	{
		libg_log_err("alloc file node failed!");
	}
	else
	{
		snprintf(node->name, sizeof(node->name) - 1, "%s", file_name);
	}
	return node;
}

int libg_fs_create(struct file_node *node)
{
	pthread_mutex_lock(&file_mutex);
	GList *list_node = g_list_find_custom(file_list, node, libg_fs_check_duplicate);
	if(list_node)
	{
		pthread_mutex_unlock(&file_mutex);
		return FS_DUPLICATE;
	}
	file_list = g_list_append(file_list, node);
	pthread_mutex_unlock(&file_mutex);
	return FS_OK;
}

int libg_fs_remove(struct file_node *node)
{
	pthread_mutex_lock(&file_mutex);
	GList *list_node = g_list_find(file_list, node);
	if(NULL == list_node)
	{
		pthread_mutex_unlock(&file_mutex);
		return FS_NO_EXIST;
	}

	file_list = g_list_remove(file_list, list_node);
	pthread_mutex_unlock(&file_mutex);
	return FS_OK;
}


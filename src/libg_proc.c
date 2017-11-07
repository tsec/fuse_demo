#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

#include "libg/libg_proc.h"
#include "libg/libg_log.h"

char *libg_get_name_by_pid(pid_t pid)
{
	static char task_name[256];
	char proc_pid_path[256];

	memset(task_name, '\0', sizeof(task_name));

	sprintf(proc_pid_path, "/proc/%d/status", pid);
	FILE *file = fopen(proc_pid_path, "r");
	if(NULL != file)
	{
		fscanf(file, "%*s %s", task_name);
		fclose(file);
	}

	return task_name;
}

pid_t libg_get_pid_by_name(char *task_name)
{
    DIR *dir;
    struct dirent *next;
    pid_t pid = 0;
    char *name;

    if(task_name == NULL)
    {
		return -EINVAL;
    }

    dir = opendir("/proc");
    if (!dir)
    {
        return -EIO;
    }
    while((next = readdir(dir)) != NULL)
    {
        if((!isdigit(next->d_name[0])) || (DT_DIR != next->d_type))
        {
			continue;
        }

		pid = strtol(next->d_name, NULL, 0);
		name = libg_get_name_by_pid(pid);
		
        if(strcmp(task_name, name) == 0)
        {
			break;
        }
    }
    closedir(dir) ;
    return pid;
}

char *libg_get_process_name()
{
	return 	libg_get_name_by_pid(getpid());
}


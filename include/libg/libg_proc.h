#ifndef _LIBG_PROC_H
#define _LIBG_PROC_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

char *libg_get_name_by_pid(pid_t pid);
pid_t libg_get_pid_by_name(char *task_name);
char *libg_get_process_name();
bool libg_judge_process_exist(char *task_name);

#ifdef __cplusplus
}
#endif

#endif





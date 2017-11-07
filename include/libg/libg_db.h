#ifndef _LIBG_DB_H
#define _LIBG_DB_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

sqlite3 *db_open(char *pcDB);
int db_close(sqlite3 *psDB);

#ifdef __cplusplus
}
#endif

#endif
/***********************************************************************
*   Copyright (C) 2016 pilot-lab.inc All rights reserved.
*   
*   @file:       database.h
*   @brief:      
*   @author:     Pilot labs
*   @maintainer: lawson.guo@pilot-lab.com.cn
*   @version:    1.0
*   @date:       2016-09-14
*   
***********************************************************************/
#ifndef _DATABASE_H
#define _DATABASE_H
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
#endif // _DATABASE_H

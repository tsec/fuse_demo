/***********************************************************************
*   Copyright (C) 2016 pilot-lab.inc All rights reserved.
*   
*   @file:       database.c
*   @brief:      
*   @author:     Pilot labs
*   @maintainer: lawson.guo@pilot-lab.com.cn
*   @version:    1.0
*   @date:       2016-09-14
*   
***********************************************************************/
#include "database.h"

sqlite3 *db_open(char *pcDB)
{
	sqlite3 *psDB = NULL;
	int nRet = 0;
	assert(pcDB);
	nRet = sqlite3_open(pcDB, &psDB);
	if(psDB == NULL)
	{
	}
	else if(nRet != SQLITE_OK)
	{
		printf("Open failed:%s\n", sqlite3_errmsg(psDB));
		sqlite3_close(psDB);
		psDB = NULL;
	}
	return psDB;
}

int db_close(sqlite3 *psDB)
{
	int nRet = 0;
	nRet = sqlite3_close(psDB);
	if(nRet != SQLITE_OK)
	{
		printf("Close failed:%s\n", sqlite3_errmsg(psDB));
		return nRet;
	}
	return nRet;
}

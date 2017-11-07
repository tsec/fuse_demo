#include "libg/libg_db.h"
#include "libg/libg_log.h"

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

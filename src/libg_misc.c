#include <sys/time.h>
#include <uuid/uuid.h>

#include "libg/libg_socket.h"
#include "libg/libg_log.h"

char *get_uuid(char *buf)
{
	//生成uuid
	uuid_t uuid;
	static char buffer[40] = {'\0'};

	uuid_generate(uuid);

	if(buf != NULL)
	{
		uuid_unparse(uuid, buf);
		return buf;
	}
	else
	{
		uuid_unparse(uuid, buffer);
		return buffer;
	}
	
	return NULL;
}


char *get_timestamp()
{
	static char buf[64];
	char tmp[64];
	memset(buf, '\0', sizeof(buf));
	memset(tmp, '\0', sizeof(tmp));
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	sprintf(tmp, " %s", ctime(&(tv.tv_sec)));
	tmp[strlen(tmp) - 1] = '\0';

	sprintf(buf, "%s %d", tmp, (int)(tv.tv_usec / 1000));
	return buf;
}



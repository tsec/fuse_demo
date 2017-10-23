#ifndef _LOG_H
#define _LOG_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <syslog.h>

#define PL_LOG_INIT(TAG, LOG_LEVEL)		openlog(TAG, LOG_CONS | LOG_PERROR | LOG_PID, LOG_USER);setlogmask(LOG_UPTO(LOG_LEVEL))

#define PL_LOG_DEBUG(fmt, arg...)	syslog(LOG_DEBUG, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define PL_LOG_INFO(fmt, arg...)	syslog(LOG_INFO, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define PL_LOG_NOTICE(fmt, arg...)	syslog(LOG_NOTICE, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define PL_LOG_WARN(fmt, arg...)	syslog(LOG_WARNING, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define PL_LOG_ERR(fmt, arg...)		syslog(LOG_ERR, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)

#endif



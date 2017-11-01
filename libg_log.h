#ifndef _LIBG_LOG_H
#define _LIBG_LOG_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define libg_log_init(TAG, LOG_LEVEL)	openlog(TAG, LOG_CONS | LOG_PERROR | LOG_PID, LOG_USER);setlogmask(LOG_UPTO(LOG_LEVEL))

#define libg_log_debug(fmt, arg...)		syslog(LOG_DEBUG, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define libg_log_info(fmt, arg...)		syslog(LOG_INFO, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define libg_log_notice(fmt, arg...)	syslog(LOG_NOTICE, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define libg_log_warning(fmt, arg...)	syslog(LOG_WARNING, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)
#define libg_log_err(fmt, arg...)		syslog(LOG_ERR, "<%s:%u>: " fmt "", basename(__FILE__), __LINE__, ##arg)

#ifdef __cplusplus
}
#endif

#endif



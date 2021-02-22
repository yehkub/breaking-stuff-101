#ifndef _YEHKUB_LOGGING_H_
#define _YEHKUB_LOGGING_H_

#include <stdarg.h>
#include <yehkub/yehkub.h>

/* Logging Levels */

/* Set Logging level */
#define LOG_LEVEL LOG_DEFAULT

#define LOG_CRITICAL    4
#define LOG_ERROR       3
#define LOG_WARNING     2
#define LOG_DEFAULT     1
#define LOG_DEBUG       0

extern bool log_written;

/* Set logfile path */
int log_set_opt(const char *filepath);

/* Write or append to log file */
ssize_t write_log(int log_level, const char* message, ...);

#endif

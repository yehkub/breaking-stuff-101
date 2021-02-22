#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <linux/limits.h>
#include <sys/types.h>

#include <yehkub/data/logging.h>

/* Path of LogFile + FileName */
char logfile[PATH_MAX];

/* Indicates if logfile has been updates, so we can print a warning message with atexit() or such thing */
bool log_written = false;

/* Set file path & name of log file */
int log_set_opt(const char *filepath) {
    if (filepath == NULL) { return EXIT_FAILURE; }
    
    size_t pathlen = strlen(filepath);

    if (pathlen > PATH_MAX - 1) { return EXIT_FAILURE; }
    snprintf(logfile, pathlen + 1, "%s", filepath);

    return EXIT_SUCCESS;
}

/* Write or append to log file */
ssize_t write_log(int log_level, const char* message, ...) {
    if (log_level < LOG_LEVEL) { return -EXIT_FAILURE; }
    va_list args;
    
    time_t now;
    size_t retsum;
    char* newline = "\n";

    va_start(args, message);
    FILE *errfp = fopen(logfile, "ab");

    if (!errfp) { return -errno; }

    /* Get current time */
    time(&now);

    char tt_time[256];

    sprintf(tt_time, ctime(&now));
    int time_len = strlen(tt_time);
    
    if (tt_time[time_len-1] == '\n') {
        tt_time[time_len-3] = 0;
    }

    size_t prefix = fprintf(errfp, "[%s]: ", tt_time);
    size_t suffix = vfprintf(errfp,message,args);
    fprintf(errfp,newline);

    va_end(args);
    fclose(errfp);

    retsum = prefix + suffix+1;

    /* Update flag indicator */
    log_written = true;

    return retsum;
}

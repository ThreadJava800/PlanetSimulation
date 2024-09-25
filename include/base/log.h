#ifndef __LOG_H__
#define __LOG_H__

#include <cstdio>
#include <cstdlib>
#include <ctime>

void closeLogFile();
void dbgPrint(const char *const fmt, ...);

#define LOG_INIT()                       \
    logfile_p = fopen(logfile_name, "a"); \
    atexit(closeLogFile);

#define LOG_PRINT(string)                                                      \
    if (logfile_p) {                                                            \
        time_t cur_time = time(NULL);                                            \
        fprintf(logfile_p, "%s: %s\n", asctime(localtime(&cur_time)), string);    \
    } else {                                                                       \
        fprintf(stderr, "Failed to write msg(%s) to log file\n", string);           \
    }

#endif
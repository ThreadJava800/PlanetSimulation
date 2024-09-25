#include "base/log.h"

static FILE *logfile_p = fopen();

void closeLogFile() {
    fclose(logfile_p);
}

void dbgPrint(const char *const fmt, ...) {
    FILE *file_ptr = stderr;
    if (logfile_p) file_ptr = logfile_p;

    va_list args;
    va_start(args, fmt);
    vfprintf(file_ptr, fmt, args);
    va_end(args);
}
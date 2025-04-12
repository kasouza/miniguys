#include "miniguys/debug.h"

#include <stdarg.h>
#include <stdio.h>

static bool s_should_log = true;

void mg_should_log(bool should_log) {
    s_should_log = should_log;
}

void mg_log_error(const char* file, int line, const char *message, ...) {
    if (!s_should_log) {
        return;
    }

    va_list args;
    va_start(args, message);
    fprintf(stderr, "\x1B[31mERROR\x1B[0m [%s, %d] - ", file, line);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");
}

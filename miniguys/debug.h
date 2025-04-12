#ifndef KASOUZA_MINIGUYS_DEBUG_H
#define KASOUZA_MINIGUYS_DEBUG_H

#include <assert.h>
#include <stdbool.h>

#define mg_LOG_ERROR(...) mg_log_error(__FILE__, __LINE__, __VA_ARGS__)

void mg_should_log(bool should_log);
void mg_log_error(const char *file, int line, const char *message, ...);

#endif

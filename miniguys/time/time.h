#ifndef KASOUZA_MINIGUYS_TIMER_TIMER_H
#define KASOUZA_MINIGUYS_TIMER_TIMER_H

#include <stdint.h>

typedef uint64_t mg_time_t;

mg_time_t mg_time();

void mg_delay(mg_time_t ms);

#endif

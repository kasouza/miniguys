#ifndef KASOUZA_MINIGUYS_TIMER_TIMER_H
#define KASOUZA_MINIGUYS_TIMER_TIMER_H

typedef struct mg_timer_t mg_Timer;

mg_Timer *mg_timer_create();
void mg_timer_free(mg_Timer *timer);

double mg_timer_deltatime(mg_Timer *timer);

#endif

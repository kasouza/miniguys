#include "SDL3/SDL_stdinc.h"
#include <SDL3/SDL_timer.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct mg_timer_t {
    Uint64 lastTime;
} mg_Timer;

mg_Timer *mg_timer_create() {
    mg_Timer *timer = malloc(sizeof(mg_Timer));
    if (timer == NULL) {
        /*mg_LOG_ERROR("Could not allocate memory for timer");*/
        return NULL;
    }

    timer->lastTime = SDL_GetTicks();

    return timer;
}

void mg_timer_free(mg_Timer *timer) { free(timer); }

double mg_timer_deltatime(mg_Timer *timer) {
    assert(timer != NULL);

    Uint64 currentTime = SDL_GetTicks();
    double deltatime = (currentTime - timer->lastTime) / 1000.0;

    timer->lastTime = currentTime;

    return deltatime;
}

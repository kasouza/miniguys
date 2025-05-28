#include "miniguys/time/time.h"
#include <SDL3/SDL_timer.h>

#include <assert.h>
#include <stdint.h>
#include <stdint.h>

uint64_t mg_time() {
    return SDL_GetTicks();
}

void mg_delay(mg_time_t ms) {
    assert(ms < UINT32_MAX && "SDL Delay: ms must be less then UINT32_MAX");
    SDL_Delay(ms);
}

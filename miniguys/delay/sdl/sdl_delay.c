#include "SDL3/SDL_timer.h"

#include <stdint.h>

void mg_delay(uint32_t ms) {
    SDL_Delay(ms);
}

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "saske.h"

#include <SDL3/SDL.h>

#include <stdio.h>

SDL_Window *s_window = NULL;
SDL_Renderer *s_renderer = NULL;

int main() {
    printf("HI %d\n", saske());

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        const char *error = SDL_GetError();
        fprintf(stderr, "Error initializing SDL %s\n", error);
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Saske", 800, 600, 0, &s_window,
                                     &s_renderer)) {
        const char *error = SDL_GetError();
        fprintf(stderr, "Error creating window and renderer %s\n", error);
        return 1;
    }

    bool is_running = true;

    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;
            default:
                break;
            }
        }

        SDL_RenderClear(s_renderer);

        SDL_FRect rect = {.x = 32, .y = 32, .w = 32, .h = 32};
        SDL_SetRenderDrawColor(s_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(s_renderer, &rect);

        SDL_RenderPresent(s_renderer);
    }

    return 0;
}

#include "sdl_renderer.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "miniguys/debug.h" // IWYU pragma: keep
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/renderer/renderer.h"

#include <SDL3/SDL_init.h>

#include <stdio.h>
#include <stdlib.h>

mg_WindowContext *mg_renderer_init(mg_EventContext *event_context) {
    assert(event_context != NULL);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        const char *message = SDL_GetError();
        fprintf(stderr, "Could not initialize SDL: %s\n", message);

        return NULL;
    }

    mg_WindowContext *context = malloc(sizeof(mg_WindowContext));
    if (context == NULL) {
        return NULL;
    }

    if (!SDL_CreateWindowAndRenderer("Saske", 800, 600, 0, &context->window,
                                     &context->renderer)) {
        const char *error = SDL_GetError();
        fprintf(stderr, "Error creating SDL window and renderer %s\n", error);

        return NULL;
    }

    context->event_context = event_context;

    return context;
}

void mg_renderer_poll_events(mg_WindowContext *context) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT: {
                mg_Event event;
                event.type = mg_EventType_WINDOW_CLOSE;
                mg_event_push(context->event_context, &event);
                break;
            }

            case SDL_EVENT_KEY_UP:
            case SDL_EVENT_KEY_DOWN: {
                mg_Action action = event.type == SDL_EVENT_KEY_UP
                                       ? mg_Action_RELEASE
                                       : mg_Action_PRESS;

                // TODO: map sdl keys
                mg_Key key = mg_Key_UNKNOWN;

                switch (event.key.key) {
                    case SDLK_LEFT:
                        key = mg_Key_LEFT;
                        break;

                    case SDLK_RIGHT:
                        key = mg_Key_RIGHT;
                        break;

                    case SDLK_UP:
                        key = mg_Key_UP;
                        break;

                    case SDLK_DOWN:
                        key = mg_Key_DOWN;
                        break;

                    case SDLK_ESCAPE:
                        key = mg_Key_ESCAPE;
                        break;
                }

                mg_Event event = {.key = {.type = mg_EventType_KEY,
                                          .key = key,
                                          .action = action}};
                mg_event_push(context->event_context, &event);

                break;
            }

            default:
                break;
        }
    }
}

void mg_renderer_render(mg_WindowContext *context, float x, float y) {
    assert(context != NULL);
    assert(context->window != NULL);
    assert(context->renderer != NULL);


    SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->renderer);

    SDL_FRect rect = {.x = x, .y = y, .w = 32, .h = 32};
    SDL_SetRenderDrawColor(context->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(context->renderer, &rect);

    SDL_RenderPresent(context->renderer);
}

void mg_renderer_terminate(mg_WindowContext *context) {
    assert(context != NULL);
    free(context);
}

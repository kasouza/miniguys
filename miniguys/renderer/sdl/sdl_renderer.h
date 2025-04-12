#ifndef KASOUZA_MINIGUYS_RENDERER_SDL_SDL_RENDERER_H
#define KASOUZA_MINIGUYS_RENDERER_SDL_SDL_RENDERER_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "miniguys/event/event.h"
#include "miniguys/math/vec2f.h"

typedef struct mg_window_context_t {
    mg_EventContext *event_context;
    SDL_Window *window;
    SDL_Renderer *renderer;
} mg_WindowContext;

typedef struct mg_texture_t {
    SDL_Texture *sdl_texture;
    mg_Vec2f size;
} mg_Texture;

#endif

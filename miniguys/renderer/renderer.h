#ifndef KASOUZA_MINIGUYS_RENDERER_RENDERER_H
#define KASOUZA_MINIGUYS_RENDERER_RENDERER_H

#include "miniguys/event/event.h"

/** Must be implemented by driver*/
typedef struct mg_window_context_t mg_WindowContext;
typedef struct mg_texture_t mg_Texture;

/** Must be impemented by driver */
mg_WindowContext *mg_renderer_init(mg_EventContext *event_context);
void mg_renderer_poll_events(mg_WindowContext *context);
void mg_renderer_terminate(mg_WindowContext *context);
void mg_renderer_render(mg_WindowContext *context, float x, float y);

mg_Texture *mg_texture_load(mg_WindowContext *context, const char* path);
void mg_texture_free(mg_Texture *texture);

#endif

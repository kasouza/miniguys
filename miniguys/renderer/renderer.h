#ifndef KASOUZA_MINIGUYS_RENDERER_RENDERER_H
#define KASOUZA_MINIGUYS_RENDERER_RENDERER_H

#include "miniguys/event/event.h"
typedef struct mg_window_context_t mg_WindowContext;

mg_WindowContext *mg_renderer_init(mg_EventContext *event_context);
void mg_renderer_poll_events(mg_WindowContext *context);
void mg_renderer_terminate(mg_WindowContext *context);
void mg_renderer_render(mg_WindowContext  *context, float x, float y);

#endif

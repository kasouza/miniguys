#ifndef KASOUZA_MINIGUYS_RENDERER_RENDERER_H
#define KASOUZA_MINIGUYS_RENDERER_RENDERER_H

#include "miniguys/event/event.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/sprite.h"

/** General */
typedef struct mg_window_context_t mg_WindowContext;

mg_WindowContext *mg_renderer_init(mg_EventContext *event_context);
void mg_renderer_terminate(mg_WindowContext *context);

void mg_renderer_poll_events(mg_WindowContext *context);
void mg_renderer_clear(mg_WindowContext *context);
void mg_renderer_present(mg_WindowContext *context);

/** Texture */
typedef struct mg_texture_t mg_Texture;

mg_Texture *mg_texture_load(mg_WindowContext *context, const char *path);
void mg_texture_free(mg_Texture *texture);

mg_Vec2f mg_texture_get_size(mg_Texture *texture);

/** Sprite */
void mg_render_sprite(mg_WindowContext *context, const mg_Sprite *sprite);

#endif

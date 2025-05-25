#ifndef KASOUZA_MINIGUYS_PLAYER_PLAYER_RENDERER
#define KASOUZA_MINIGUYS_PLAYER_PLAYER_RENDERER

#include "miniguys/input/input.h"
#include "miniguys/player/player.h"

typedef struct mg_player_renderer_t mg_PlayerRenderer;

mg_PlayerRenderer *mg_player_renderer_create(mg_WindowContext *window_context);
void mg_player_renderer_free(mg_PlayerRenderer *player_renderer);

void mg_player_renderer_render_player(const mg_PlayerRenderer *player_renderer,
                      const mg_Player *player);

#endif

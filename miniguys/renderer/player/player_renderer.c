#include "miniguys/config/config.h"
#include "miniguys/debug.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/player/player.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sprite.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mg_player_renderer_t {
    mg_Sprite *player_sprite;
    mg_WindowContext *window_context;
} mg_PlayerRenderer;

mg_PlayerRenderer *mg_player_renderer_create(mg_WindowContext *window_context) {
    assert(window_context != NULL);

    mg_PlayerRenderer *player_renderer = malloc(sizeof(*player_renderer));
    if (player_renderer == NULL) {
        mg_LOG_ERROR("Could not allocate memory for player renderer");
        return NULL;
    }

    player_renderer->window_context = window_context;

    player_renderer->player_sprite =
        mg_sprite_load(window_context, PLAYER_SPRITE_PATH);
    if (player_renderer->player_sprite == NULL) {
        mg_LOG_ERROR("Could not load player sprite");
        free(player_renderer);
        return NULL;
    }

    mg_Vec2f sprite_size = mg_sprite_get_size(player_renderer->player_sprite);
    mg_sprite_set_pivot(player_renderer->player_sprite,
                        (mg_Vec2f){sprite_size.x / 2, sprite_size.y / 2});

    return player_renderer;
}

void mg_player_renderer_free(mg_PlayerRenderer *player_renderer) {
    assert(player_renderer != NULL);

    if (player_renderer->player_sprite != NULL) {
        mg_sprite_free(player_renderer->player_sprite);
        player_renderer->player_sprite = NULL;
    }

    free(player_renderer);
}

void mg_player_renderer_render_player(const mg_PlayerRenderer *player_renderer,
                                      const mg_Player *player) {
    mg_sprite_set_position(player_renderer->player_sprite,
                           mg_player_get_position(player));
    mg_sprite_set_rotation(player_renderer->player_sprite,
                           mg_player_get_rotation(player));
    mg_render_sprite(player_renderer->window_context,
                     player_renderer->player_sprite);
}

#include "miniguys/game/game.h"
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/player/player.h"
#include "miniguys/renderer/player/player_renderer.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/time/time.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct mg_game_t {
    bool is_running;
    mg_WindowContext *window_context;
    mg_EventContext *event_context;
    mg_InputContext *input_context;

    mg_PlayerRenderer *player_renderer;
    mg_Player *player;
} mg_Game;

mg_Game *mg_game_create() {
    mg_EventContext *event_context = mg_event_init();
    if (event_context == NULL) {
        return NULL;
    }

    mg_WindowContext *window_context = mg_renderer_init(event_context);
    if (window_context == NULL) {
        return NULL;
    }

    mg_InputContext *input_context = mg_input_init();
    if (input_context == NULL) {
        return NULL;
    }

    mg_Player *player = mg_player_create();
    if (player == NULL) {
        return NULL;
    }

    mg_player_set_position(player, (mg_Vec2f){.x = 32.0f, .y = 32.0f});

    mg_PlayerRenderer *player_renderer =
        mg_player_renderer_create(window_context);
    if (player == NULL) {
        return NULL;
    }

    mg_Game *game = malloc(sizeof(*game));

    game->is_running = false;

    game->window_context = window_context;
    game->event_context = event_context;
    game->input_context = input_context;

    game->player_renderer = player_renderer;
    game->player = player;

    return game;
}

void mg_game_free(mg_Game *game) {
    assert(game != NULL);

    mg_player_free(game->player);
    game->player = NULL;

    mg_player_renderer_free(game->player_renderer);
    game->player_renderer = NULL;

    mg_input_terminate(game->input_context);
    game->input_context = NULL;

    mg_renderer_terminate(game->window_context);
    game->window_context = NULL;

    mg_event_terminate(game->event_context);
    game->event_context = NULL;

    free(game);
}

void mg_game_handle_events(mg_Game *game, double deltatime) {
    assert(game != NULL);
    mg_renderer_poll_events(game->window_context);

    mg_Event event;

    while (mg_event_poll(game->event_context, &event)) {
        switch (event.type) {
            case mg_EventType_WINDOW_CLOSE:
                game->is_running = false;
                break;

            case mg_EventType_KEY:
                mg_input_handle_key_event(game->input_context, &event.key);
                break;

            default:
                break;
        }
    }
}

void mg_game_update(mg_Game *game, double deltatime) {
    assert(game != NULL);

    if (mg_input_is_key_pressed(game->input_context, mg_Key_ESCAPE)) {
        game->is_running = false;
    }

    mg_Vec2f dir = {0};

    if (mg_input_is_key_pressed(game->input_context, mg_Key_LEFT)) {
        dir.x = -1;
    } else if (mg_input_is_key_pressed(game->input_context, mg_Key_RIGHT)) {
        dir.x = 1;
    }

    if (mg_input_is_key_pressed(game->input_context, mg_Key_UP)) {
        dir.y = -1;
    } else if (mg_input_is_key_pressed(game->input_context, mg_Key_DOWN)) {
        dir.y = 1;
    }

    mg_vec2f_normalize(&dir);
    mg_vec2f_scale(&dir, 64 * deltatime);

    mg_player_move(game->player, dir);
    mg_player_rotate(game->player, deltatime);
}

void mg_game_render(mg_Game *game, double deltatime) {
    mg_renderer_clear(game->window_context);
    mg_player_renderer_render_player(game->player_renderer, game->player);
    mg_renderer_present(game->window_context);
}

void mg_game_loop(mg_Game *game) {
    assert(game != NULL);

    game->is_running = true;

    int desired_fps = 60;
    mg_time_t desired_frame_time = 1000 / desired_fps;

    double deltatime = 0;

    while (game->is_running) {
        mg_time_t start = mg_time();

        mg_game_handle_events(game, deltatime);
        mg_game_update(game, deltatime);
        mg_game_render(game, deltatime);

        // Frametime
        mg_time_t end = mg_time();
        mg_time_t frametime = end - start;

        mg_time_t diff = desired_frame_time - frametime;

        if (diff > 0) {
            mg_delay(diff);
        }

        mg_time_t total_end = mg_time();
        deltatime = (total_end - start) / 1000.0;
    }
}

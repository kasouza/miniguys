#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/player/player.h"
#include "miniguys/player/player_renderer.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sprite.h"

#include <SDL3/SDL.h>

#include <stdio.h>

int main() {
    mg_EventContext *event_context = mg_event_init();
    if (event_context == NULL) {
        return 1;
    }

    mg_WindowContext *window_context = mg_renderer_init(event_context);
    if (window_context == NULL) {
        return 1;
    }

    mg_InputContext *input_context = mg_input_init();
    if (input_context == NULL) {
        return 1;
    }

    bool is_running = true;

    float x = 0;
    float y = 0;

    Uint64 now = 0;
    Uint64 last = SDL_GetTicks();
    double target_fps = 60.0;
    double target_deltatime = 1.0 / target_fps;

    mg_Player *player = mg_player_create();
    mg_PlayerRenderer *player_renderer =
        mg_player_renderer_create(window_context);

    // TODO
    //  - Abstrair o deltatime

    while (is_running) {
        now = SDL_GetTicks();
        Uint64 diff = now - last;

        double deltatime = diff / 1000.0;
        double fps = 1.0 / deltatime;

        last = now;
        mg_renderer_poll_events(window_context);

        mg_Event event;

        while (mg_event_poll(event_context, &event)) {
            switch (event.type) {
                case mg_EventType_WINDOW_CLOSE:
                    is_running = false;
                    break;

                case mg_EventType_KEY:
                    mg_input_handle_key_event(input_context, &event.key);
                    break;

                default:
                    break;
            }
        }

        if (mg_input_is_key_pressed(input_context, mg_Key_ESCAPE)) {
            is_running = false;
        }

        mg_Vec2f player_pos = mg_player_get_position(player);

        if (mg_input_is_key_pressed(input_context, mg_Key_LEFT)) {
            player_pos.x -= 32 * deltatime;
        } else if (mg_input_is_key_pressed(input_context, mg_Key_RIGHT)) {
            player_pos.x += 32 * deltatime;
        }

        if (mg_input_is_key_pressed(input_context, mg_Key_UP)) {
            player_pos.y -= 32 * deltatime;
        } else if (mg_input_is_key_pressed(input_context, mg_Key_DOWN)) {
            player_pos.y += 32 * deltatime;
        }

        mg_player_set_position(player, player_pos);
        mg_player_rotate(player, deltatime);

        mg_renderer_clear(window_context);
        mg_player_renderer_render_player(player_renderer, player);
        mg_renderer_present(window_context);

        double diff_in_seconds = diff / 1000.0;
        double delay_in_seconds = target_deltatime - diff_in_seconds;

        if (delay_in_seconds > 0) {
            SDL_Delay((Uint64)delay_in_seconds * 1000);
        }
    }

    mg_player_renderer_free(player_renderer);
    player_renderer = NULL;

    mg_player_free(player);
    player = NULL;

    mg_input_terminate(input_context);
    input_context = NULL;

    mg_renderer_terminate(window_context);
    window_context = NULL;

    return 0;
}

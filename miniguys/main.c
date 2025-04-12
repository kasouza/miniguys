#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sprite.h"

#include <SDL3/SDL.h>

#include <stdio.h>

SDL_Window *s_window = NULL;
SDL_Renderer *s_renderer = NULL;

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

    mg_Sprite *sprite = mg_sprite_load(window_context, "assets/test/amogus_32x32.png");
    sprite->pivot.x = sprite->size.x / 2;
    sprite->pivot.y = sprite->size.y / 2;

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

        if (mg_input_is_key_pressed(input_context, mg_Key_LEFT)) {
            sprite->position.x -= 32 * deltatime;
        } else if (mg_input_is_key_pressed(input_context, mg_Key_RIGHT)) {
            sprite->position.x += 32 * deltatime;
        }

        if (mg_input_is_key_pressed(input_context, mg_Key_UP)) {
            sprite->position.y -= 32 * deltatime;
        } else if (mg_input_is_key_pressed(input_context, mg_Key_DOWN)) {
            sprite->position.y += 32 * deltatime;
        }

        sprite->rotation += deltatime;
        printf("%f\n", sprite->rotation);
        
        mg_renderer_clear(window_context);
        mg_render_sprite(window_context, sprite);
        mg_renderer_present(window_context);

        double diff_in_seconds = diff / 1000.0;
        double delay_in_seconds = target_deltatime - diff_in_seconds;

        if (delay_in_seconds > 0) {
            SDL_Delay((Uint64)delay_in_seconds * 1000);
        }
    }

    mg_sprite_free(sprite);

    mg_input_terminate(input_context);
    input_context = NULL;

    mg_renderer_terminate(window_context);
    window_context = NULL;

    return 0;
}

#include "miniguys/player/player_controller.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/player/player.h"

void mg_player_controller_update(mg_InputContext *input_context,
                                 mg_Player *player, double deltatime) {
    // Look
    mg_Vec2f mouse_pos = mg_input_get_mouse_pos(input_context);
    mg_Vec2f look_dir = mg_vec2f_sub(mouse_pos, mg_player_get_position(player));
    mg_vec2f_normalize(&look_dir);
    mg_player_set_look_direction(player, look_dir);

    // Movement
    mg_Vec2f move_dir = {0};

    if (mg_input_is_key_pressed(input_context, mg_Key_A)) {
        move_dir.x = -1;
    } else if (mg_input_is_key_pressed(input_context, mg_Key_D)) {
        move_dir.x = 1;
    }

    if (mg_input_is_key_pressed(input_context, mg_Key_W)) {
        move_dir.y = -1;
    } else if (mg_input_is_key_pressed(input_context, mg_Key_S)) {
        move_dir.y = 1;
    }

    if (mg_vec2f_length(move_dir) > 0.0f) {
        mg_vec2f_normalize(&move_dir);
        mg_vec2f_scale(&move_dir, mg_player_get_max_speed(player));
        mg_player_set_velocity(player, move_dir);
    } else {
        mg_Vec2f velocity = mg_player_get_velocity(player);
        float speed = mg_vec2f_length(velocity);
        if (speed > 0.0f) {
            speed *= mg_player_get_decelaration_factor(player) * deltatime;
            if (speed < 0.1f) {
                speed = 0.0f;
            }

            mg_vec2f_normalize(&velocity);
            mg_vec2f_scale(&velocity, speed);
            mg_player_set_velocity(player, velocity);
        }
    }

    mg_player_apply_velocity(player);
}

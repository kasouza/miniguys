#include "miniguys/player/player_controller.h"

void mg_player_controller_update(mg_InputContext *input_context,
                                 mg_Player *player, double deltatime) {
    mg_Vec2f dir = {0};

    if (mg_input_is_key_pressed(input_context, mg_Key_LEFT)) {
        dir.x = -1;
    } else if (mg_input_is_key_pressed(input_context, mg_Key_RIGHT)) {
        dir.x = 1;
    }

    if (mg_input_is_key_pressed(input_context, mg_Key_UP)) {
        dir.y = -1;
    } else if (mg_input_is_key_pressed(input_context, mg_Key_DOWN)) {
        dir.y = 1;
    }

    mg_vec2f_normalize(&dir);
    mg_vec2f_scale(&dir, 64 * deltatime);

    mg_player_move(player, dir);
    mg_player_rotate(player, deltatime);
}

#include "miniguys/player/player_controller.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"

void mg_player_controller_update(mg_InputContext *input_context,
                                 mg_Player *player, double deltatime) {
    mg_Vec2f dir = {0};

    if (mg_input_is_key_pressed(input_context, mg_Key_A)) {
        dir.x = -1;
    } else if (mg_input_is_key_pressed(input_context, mg_Key_D)) {
        dir.x = 1;
    }

    if (mg_input_is_key_pressed(input_context, mg_Key_W)) {
        dir.y = -1;
    } else if (mg_input_is_key_pressed(input_context, mg_Key_S)) {
        dir.y = 1;
    }

    mg_vec2f_normalize(&dir);
    mg_vec2f_scale(&dir, 64 * deltatime);

    mg_player_move(player, dir);

    mg_Vec2f mouse_pos = mg_input_get_mouse_pos(input_context);
    mg_Vec2f look_dir = mg_vec2f_sub(mouse_pos, mg_player_get_position(player));
    mg_vec2f_normalize(&look_dir);

    mg_player_set_direction(player, look_dir);

    /*mg_player_rotate(player, deltatime);*/
}

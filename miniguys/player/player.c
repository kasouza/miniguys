#include "miniguys/debug.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/sprite.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mg_player_t {
    mg_Vec2f pos;
    mg_Vec2f look_dir;

    mg_Vec2f velocity;

    float max_speed;
    float decelaration_factor;
} mg_Player;

mg_Player *mg_player_create(mg_Sprite *sprite) {
    mg_Player *player = calloc(1, sizeof(*player));
    if (player == NULL) {
        mg_LOG_ERROR("Could not allocate memory for player");
        return NULL;
    }

    player->pos.x = 0;
    player->pos.y = 0;

    player->look_dir.x = 1;
    player->look_dir.y = 0;

    player->velocity.x = 0;
    player->velocity.y = 0;

    player->max_speed = 8;
    player->decelaration_factor = 0.9f;

    return player;
}

void mg_player_free(mg_Player *player) {
    assert(player != NULL);
    free(player);
}

mg_Vec2f mg_player_get_position(const mg_Player *player) {
    assert(player != NULL);
    return player->pos;
}

void mg_player_set_position(mg_Player *player, mg_Vec2f pos) {
    assert(player != NULL);
    player->pos = pos;
}

void mg_player_move(mg_Player *player, mg_Vec2f offset) {
    assert(player != NULL);

    player->pos.x += offset.x;
    player->pos.y += offset.y;
}

void mg_player_move_x(mg_Player *player, double x_offset) {
    player->pos.x += x_offset;
}

void mg_player_move_y(mg_Player *player, double y_offset) {
    player->pos.y += y_offset;
}

void mg_player_rotate(mg_Player *player, float radians) {
    assert(player != NULL);
    mg_vec2f_rotate(&player->look_dir, radians);
}

double mg_player_get_rotation(const mg_Player *player) {
    assert(player != NULL);
    return atan2(player->look_dir.y, player->look_dir.x);
}

void mg_player_set_look_direction(mg_Player *player, mg_Vec2f dir) {
    assert(player != NULL);
    player->look_dir = dir;
}

void mg_player_set_velocity(mg_Player *player, mg_Vec2f velocity) {
    assert(player != NULL);
    player->velocity = velocity;
}

mg_Vec2f mg_player_get_velocity(const mg_Player *player) {
    assert(player != NULL);
    return player->velocity;
}

void mg_player_apply_velocity(mg_Player *player) {
    assert(player != NULL);

    player->pos.x += player->velocity.x;
    player->pos.y += player->velocity.y;
}

float mg_player_get_max_speed(const mg_Player *player) {
    assert(player != NULL);
    return player->max_speed;
}

float mg_player_get_decelaration_factor(const mg_Player *player) {
    assert(player != NULL);
    return player->decelaration_factor;
}

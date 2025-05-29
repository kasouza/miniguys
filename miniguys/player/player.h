#ifndef KASOUZA_MINIGUYS_PLAYER_PLAYER_H
#define KASOUZA_MINIGUYS_PLAYER_PLAYER_H

#include "miniguys/math/vec2f.h"
typedef struct mg_player_t mg_Player;

mg_Player *mg_player_create();
void mg_player_free(mg_Player *player);

mg_Vec2f mg_player_get_position(const mg_Player *player);
void mg_player_set_position(mg_Player *player, mg_Vec2f pos);

void mg_player_move(mg_Player *player, mg_Vec2f offset);
void mg_player_move_x(mg_Player *player, double x_offset);
void mg_player_move_y(mg_Player *player, double y_offset);

void mg_player_rotate(mg_Player *player, float radians);
double mg_player_get_rotation(const mg_Player *player);

void mg_player_set_look_direction(mg_Player *player, mg_Vec2f dir);

void mg_player_set_velocity(mg_Player *player, mg_Vec2f velocity);
mg_Vec2f mg_player_get_velocity(const mg_Player *player);

void mg_player_apply_velocity(mg_Player *player);

float mg_player_get_max_speed(const mg_Player *player);
float mg_player_get_decelaration_factor(const mg_Player *player);

#endif

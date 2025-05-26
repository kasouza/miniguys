#ifndef KASOUZA_MINIGUYS_PLAYER_PLAYER_H
#define KASOUZA_MINIGUYS_PLAYER_PLAYER_H

#include "miniguys/math/vec2f.h"
typedef struct mg_player_t mg_Player;

mg_Player *mg_player_create();

mg_Vec2f mg_player_get_position(const mg_Player *player);
void mg_player_set_position(mg_Player *player, mg_Vec2f pos);

void mg_player_move(mg_Player *player, mg_Vec2f offset);
void mg_player_move_x(mg_Player *player, double x_offset);
void mg_player_move_y(mg_Player *player, double y_offset);

void mg_player_rotate(mg_Player *player, double radians);
double mg_player_get_rotation(const mg_Player *player);

void mg_player_free(mg_Player *player);

#endif

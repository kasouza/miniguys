#ifndef KASOUZA_MINIGUYS_PLAYER_PLAYER_CONTROLLER_H
#define KASOUZA_MINIGUYS_PLAYER_PLAYER_CONTROLLER_H

#include "miniguys/input/input.h"
#include "miniguys/player/player.h"

void mg_player_controller_update(mg_InputContext *input_context,
                                 mg_Player *player, double deltatime);

#endif

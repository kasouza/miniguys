#include "miniguys/debug.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/sprite.h"

#include <stdlib.h>

typedef struct mg_player_t {
    mg_Vec2f pos;
    double rotation;
} mg_Player;

mg_Player *mg_player_create(mg_Sprite *sprite) {
    mg_Player *player = malloc(sizeof(*player));
    if (player == NULL) {
        mg_LOG_ERROR("Could not allocate memory for player");
        return NULL;
    }

    player->pos.x = 0;
    player->pos.y = 0;

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

void mg_player_rotate(mg_Player *player, double radians) {
    assert(player != NULL);
    player->rotation += radians;
}

double mg_player_get_rotation(const mg_Player *player) {
    assert(player != NULL);
    return player->rotation;
}

#include "miniguys/game/game.h"

#include <SDL3/SDL.h>

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

int main() {
    mg_Game *game = mg_game_create();

    mg_game_loop(game);

    mg_game_free(game);
    game = NULL;

    return 0;
}

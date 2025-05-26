#include "miniguys/game/game.h"

#include <SDL3/SDL.h>

#include <stdio.h>

int main() {
    mg_Game *game = mg_game_create();

    mg_game_loop(game);

    mg_game_free(game);
    game = NULL;

    /*Uint64 now = 0;*/
    /*Uint64 last = SDL_GetTicks();*/
    /*double target_fps = 60.0;*/
    /*double target_deltatime = 1.0 / target_fps;*/


    /*while (is_running) {*/
        /*now = SDL_GetTicks();*/
        /*Uint64 diff = now - last;*/

        /*double deltatime = diff / 1000.0;*/
        /*double fps = 1.0 / deltatime;*/

        /*last = now;*/

        /*double diff_in_seconds = diff / 1000.0;*/
        /*double delay_in_seconds = target_deltatime - diff_in_seconds;*/

        /*if (delay_in_seconds > 0) {*/
            /*SDL_Delay((Uint64)delay_in_seconds * 1000);*/
        /*}*/
    /*}*/

    return 0;
}

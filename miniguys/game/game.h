#ifndef KASOUZA_MINIGUYS_GAME_GAME_H
#define KASOUZA_MINIGUYS_GAME_GAME_H

typedef struct mg_game_t mg_Game;
mg_Game *mg_game_create();

void mg_game_free(mg_Game *game);

void mg_game_handle_events(mg_Game *game, double deltatime);

void mg_game_update(mg_Game *game, double deltatime);

void mg_game_render(mg_Game *game, double deltatime);

void mg_game_loop(mg_Game *game);

#endif

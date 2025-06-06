#ifndef KASOUZA_MINIGUYS_RENDERER_SPRITE_H
#define KASOUZA_MINIGUYS_RENDERER_SPRITE_H

#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
typedef struct mg_texture_t mg_Texture;

typedef struct mg_sprite_t {
    mg_Texture *texture;

    mg_Vec2f position;
    mg_Vec2f size;

    mg_Vec2f pivot;

    float rotation;
} mg_Sprite;

mg_Sprite *mg_sprite_load(mg_WindowContext *context, const char* path);
void mg_sprite_free(mg_Sprite *sprite);

void mg_sprite_set_position(mg_Sprite *sprite, mg_Vec2f pos);
void mg_sprite_set_rotation(mg_Sprite *sprite, float rotation);
void mg_sprite_set_pivot(mg_Sprite *sprite, mg_Vec2f pivot);

mg_Vec2f mg_sprite_get_size(const mg_Sprite *sprite);

#endif

#include "sprite.h"
#include "miniguys/debug.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/renderer.h"

#include <stddef.h>
#include <stdlib.h>

mg_Sprite *mg_sprite_load(mg_WindowContext *context, const char *path) {
    assert(context != NULL);
    assert(path != NULL);

    mg_Texture *texture = mg_texture_load(context, path);
    if (texture == NULL) {
        return NULL;
    }

    mg_Vec2f size = mg_texture_get_size(texture);

    mg_Sprite *sprite = calloc(1, sizeof(mg_Sprite));
    if (sprite == NULL) {
        mg_LOG_ERROR("Could not allocate memory for sprite");
        mg_texture_free(texture);
        return NULL;
    }

    sprite->texture = texture;
    sprite->size = size;

    return sprite;
}

void mg_sprite_free(mg_Sprite *sprite) {
    assert(sprite != NULL);

    mg_texture_free(sprite->texture);
    free(sprite);
}

void mg_sprite_set_position(mg_Sprite *sprite, mg_Vec2f pos) {
    assert(sprite != NULL);

    sprite->position.x = pos.x;
    sprite->position.y = pos.y;
}

void mg_sprite_set_rotation(mg_Sprite *sprite, float rotation) {
    assert(sprite != NULL);

    sprite->rotation = rotation;
}

void mg_sprite_set_pivot(mg_Sprite *sprite, mg_Vec2f pivot) {
    assert(sprite != NULL);

    sprite->pivot.x = pivot.x;
    sprite->pivot.y = pivot.y;
}

mg_Vec2f mg_sprite_get_size(const mg_Sprite *sprite) {
    assert(sprite != NULL);

    return sprite->size;
}

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

#include "miniguys/math/vec2f.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>

float mg_vec2f_length(mg_Vec2f vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void mg_vec2f_normalize(mg_Vec2f *vec) {
    assert(vec != NULL);

    float len = mg_vec2f_length(*vec);

    if (len > 0.0f) {
        vec->x /= len;
        vec->y /= len;
    } else {
        vec->x = 0.0f;
        vec->y = 0.0f;
    }
}

void mg_vec2f_clamp(mg_Vec2f *vec, float len) {
    assert(vec != NULL);

    float current_length = mg_vec2f_length(*vec);
    if (current_length > len) {
        mg_vec2f_normalize(vec);
        mg_vec2f_scale(vec, len);
    }
}

void mg_vec2f_scale(mg_Vec2f *vec, float scalar) {
    assert(vec != NULL);

    vec->x *= scalar;
    vec->y *= scalar;
}

void mg_vec2f_rotate(mg_Vec2f *vec, float radians) {
    assert(vec != NULL);

    float cs = cos(radians);
    float sn = sin(radians);

    float x = vec->x;
    float y = vec->y;

    vec->x = x * cs - y * sn;
    vec->y = x * sn + y * cs;
}

mg_Vec2f mg_vec2f_sub(mg_Vec2f a, mg_Vec2f b) {
    return (mg_Vec2f){.x = a.x - b.x, .y = a.y - b.y};
}

void mg_vec2f_invert(mg_Vec2f *vec) {
    assert(vec != NULL);
    vec->x = -vec->x;
    vec->y = -vec->y;
}

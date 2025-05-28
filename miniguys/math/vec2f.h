#ifndef KASOUZA_MINIGUYS_MATH_VEC2f_H
#define KASOUZA_MINIGUYS_MATH_VEC2f_H

typedef struct mg_vec2f_t {
    float x;
    float y;
} mg_Vec2f;

float mg_vec2f_length(mg_Vec2f vec);
void mg_vec2f_normalize(mg_Vec2f *vec);
void mg_vec2f_scale(mg_Vec2f *vec, float scalar);

mg_Vec2f mg_vec2f_sub(mg_Vec2f a, mg_Vec2f b);

#endif

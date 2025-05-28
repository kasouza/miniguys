#ifndef KASOUZA_MINIGUYS_INPUT_INPUT_H
#define KASOUZA_MINIGUYS_INPUT_INPUT_H

#include "miniguys/event/event.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/input/key.h"

#include <stdbool.h>

typedef struct mg_key_event_t mg_KeyEvent;
typedef struct mg_window_context_t mg_WindowContext;


typedef struct mg_input_context_t mg_InputContext;

mg_InputContext *mg_input_init();

void mg_input_handle_key_event(mg_InputContext *context, mg_KeyEvent *event);
void mg_input_handle_mouse_motion_event(mg_InputContext *context,
                                        const mg_MouseMotionEvent *event);

bool mg_input_is_key_pressed(const mg_InputContext *context, mg_Key key);
void mg_input_terminate(mg_InputContext *context);

mg_Vec2f mg_input_get_mouse_pos(const mg_InputContext *context);

#endif

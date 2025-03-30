#include "miniguys/input/input.h"
#include "miniguys/debug.h" // IWYU pragma: keep
#include "miniguys/event/event.h"

#include <stdio.h>
#include <stdlib.h>

mg_InputContext *mg_input_init() {
    mg_InputContext *context = calloc(1, sizeof(mg_InputContext));
    if (context == NULL) {
        fprintf(stderr, "Could not allocate memory for input context\n");
        return NULL;
    }

    return context;
}

void mg_input_handle_key_event(mg_InputContext *context, mg_KeyEvent *event) {
    assert(context != NULL);
    assert(event != NULL);
    assert(event->key > mg_Key_FIRST && event->key < mg_Key_LAST);

    bool pressed = event->action == mg_Action_PRESS;
    context->pressed[event->key] = pressed;
}

bool mg_input_is_key_pressed(mg_InputContext *context, mg_Key key) {
    assert(context != NULL);
    assert(key > mg_Key_FIRST && key < mg_Key_LAST);

    return context->pressed[key];
}

void mg_input_terminate(mg_InputContext *context) {
    assert(context != NULL);

    free(context);
}

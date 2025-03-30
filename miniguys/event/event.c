#include "event.h"
#include "miniguys/debug.h" // IWYU pragma: keep

#include <stdio.h>
#include <stdlib.h>

mg_EventContext *mg_event_init() {
    mg_EventContext *context = malloc(sizeof(mg_EventContext));
    if (context == NULL) {
        fprintf(stderr, "Could not allocate memory for event context\n");
        return NULL;
    }

    context->event_queue_len = 0;
    context->event_queue_cap = 32;
    context->event_queue = malloc(sizeof(mg_Event) * context->event_queue_cap);

    if (context->event_queue == NULL) {
        fprintf(stderr, "Could not allocate memory for event queue\n");
        free(context);
        return NULL;
    }

    return context;
}

void mg_event_terminate(mg_EventContext *context) {
    assert(context != NULL);

    free(context->event_queue);
    free(context);
}

void mg_event_push(mg_EventContext *context, mg_Event *event) {
    assert(context != NULL && context->event_queue != NULL);
    assert(event != NULL);

    int new_len = context->event_queue_len + 1;

    if (new_len >= context->event_queue_cap) {
        context->event_queue_cap *= 2;
        context->event_queue =
            realloc(context->event_queue,
                    context->event_queue_cap * sizeof(*context->event_queue));

        if (context->event_queue == NULL) {
            fprintf(stderr, "Could not reallocate memory for event queue\n");
            return;
        }
    }

    context->event_queue[context->event_queue_len] = *event;
    context->event_queue_len++;
}

bool mg_event_poll(mg_EventContext *context, mg_Event *event) {
    assert(context != NULL && context->event_queue != NULL);
    assert(event != NULL);

    if (context->event_queue_len == 0) {
        event->type = mg_EventType_NONE;
        return false;
    }

    *event = context->event_queue[0];

    for (int i = 1; i < context->event_queue_len; ++i) {
        context->event_queue[i - 1] = context->event_queue[i];
    }

    context->event_queue_len--;

    return true;
}

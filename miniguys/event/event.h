#ifndef KASOUZA_MINIGUYS_EVENT_EVENT_H
#define KASOUZA_MINIGUYS_EVENT_EVENT_H

#include "miniguys/input/input.h"
#include <stdbool.h>

/** Event types */
typedef enum mg_event_type {
    mg_EventType_NONE = 0,
    mg_EventType_WINDOW_CLOSE,
    mg_EventType_KEY,
    mg_EventType_COUNT
} mg_EventType;

/** Event structs */
typedef struct mg_window_close_event_t {
    mg_EventType type;
} mg_WindowCloseEvent;

typedef struct mg_key_event_t {
    mg_EventType type;
    mg_Key key;
    mg_Action action;
} mg_KeyEvent;

/** Union of all event types */
typedef union {
    mg_EventType type;

    mg_WindowCloseEvent window_close;
    mg_KeyEvent key;
} mg_Event;

typedef struct mg_event_context_h {
    mg_Event *event_queue;
    int event_queue_len;
    int event_queue_cap;
} mg_EventContext;

mg_EventContext *mg_event_init();
void mg_event_terminate(mg_EventContext *context);

void mg_event_push(mg_EventContext *context, mg_Event *event);
bool mg_event_poll(mg_EventContext *context, mg_Event *event);

#endif

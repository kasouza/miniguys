#include "sdl_renderer.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"
#include "SDL3_image/SDL_image.h"
#include "miniguys/debug.h" // IWYU pragma: keep
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/renderer.h"

#include <SDL3/SDL_init.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_key_event(mg_WindowContext *context, SDL_KeyboardEvent *event);

mg_WindowContext *mg_renderer_init(mg_EventContext *event_context) {
    assert(event_context != NULL);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        const char *message = SDL_GetError();
        mg_LOG_ERROR("Could not initialize SDL: %s\n", message);

        return NULL;
    }

    mg_WindowContext *context = malloc(sizeof(mg_WindowContext));
    if (context == NULL) {
        return NULL;
    }

    if (!SDL_CreateWindowAndRenderer("Saske", 800, 600, 0, &context->window,
                                     &context->renderer)) {
        const char *error = SDL_GetError();
        mg_LOG_ERROR("Error creating SDL window and renderer %s\n", error);

        return NULL;
    }

    context->event_context = event_context;

    return context;
}

void mg_renderer_poll_events(mg_WindowContext *context) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT: {
                mg_Event event;
                event.type = mg_EventType_WINDOW_CLOSE;
                mg_event_push(context->event_context, &event);
                break;
            }

            case SDL_EVENT_KEY_UP:
            case SDL_EVENT_KEY_DOWN:
                handle_key_event(context, &event.key);
                break;

            default:
                break;
        }
    }
}

void mg_renderer_render(mg_WindowContext *context, float x, float y) {
    assert(context != NULL);
    assert(context->window != NULL);
    assert(context->renderer != NULL);

    SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->renderer);

    SDL_FRect rect = {.x = x, .y = y, .w = 32, .h = 32};
    SDL_SetRenderDrawColor(context->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(context->renderer, &rect);

    SDL_RenderPresent(context->renderer);
}

void mg_renderer_terminate(mg_WindowContext *context) {
    assert(context != NULL);
    free(context);
}

void handle_key_event(mg_WindowContext *context, SDL_KeyboardEvent *event) {
    assert(context != NULL);
    assert(event != NULL);

    mg_Action action =
        event->type == SDL_EVENT_KEY_UP ? mg_Action_RELEASE : mg_Action_PRESS;

    mg_Key key = mg_Key_UNKNOWN;

    // Can't use a regular array table because SDL's values are too sparse.
    // Tried a hash map but it is actually a little bit slower, só ended up
    // just sticking to the good old switch
    switch (event->key) {
        case SDLK_RETURN:
            key = mg_Key_RETURN;
            break;

        case SDLK_ESCAPE:
            key = mg_Key_ESCAPE;
            break;

        case SDLK_BACKSPACE:
            key = mg_Key_BACKSPACE;
            break;

        case SDLK_TAB:
            key = mg_Key_TAB;
            break;

        case SDLK_SPACE:
            key = mg_Key_SPACE;
            break;

        case SDLK_EXCLAIM:
            key = mg_Key_EXCLAIM;
            break;

        case SDLK_DBLAPOSTROPHE:
            key = mg_Key_DBLAPOSTROPHE;
            break;

        case SDLK_HASH:
            key = mg_Key_HASH;
            break;

        case SDLK_DOLLAR:
            key = mg_Key_DOLLAR;
            break;

        case SDLK_PERCENT:
            key = mg_Key_PERCENT;
            break;

        case SDLK_AMPERSAND:
            key = mg_Key_AMPERSAND;
            break;

        case SDLK_APOSTROPHE:
            key = mg_Key_APOSTROPHE;
            break;

        case SDLK_LEFTPAREN:
            key = mg_Key_LEFTPAREN;
            break;

        case SDLK_RIGHTPAREN:
            key = mg_Key_RIGHTPAREN;
            break;

        case SDLK_ASTERISK:
            key = mg_Key_ASTERISK;
            break;

        case SDLK_PLUS:
            key = mg_Key_PLUS;
            break;

        case SDLK_COMMA:
            key = mg_Key_COMMA;
            break;

        case SDLK_MINUS:
            key = mg_Key_MINUS;
            break;

        case SDLK_PERIOD:
            key = mg_Key_PERIOD;
            break;

        case SDLK_SLASH:
            key = mg_Key_SLASH;
            break;

        case SDLK_0:
            key = mg_Key_0;
            break;

        case SDLK_1:
            key = mg_Key_1;
            break;

        case SDLK_2:
            key = mg_Key_2;
            break;

        case SDLK_3:
            key = mg_Key_3;
            break;

        case SDLK_4:
            key = mg_Key_4;
            break;

        case SDLK_5:
            key = mg_Key_5;
            break;

        case SDLK_6:
            key = mg_Key_6;
            break;

        case SDLK_7:
            key = mg_Key_7;
            break;

        case SDLK_8:
            key = mg_Key_8;
            break;

        case SDLK_9:
            key = mg_Key_9;
            break;

        case SDLK_COLON:
            key = mg_Key_COLON;
            break;

        case SDLK_SEMICOLON:
            key = mg_Key_SEMICOLON;
            break;

        case SDLK_LESS:
            key = mg_Key_LESS;
            break;

        case SDLK_EQUALS:
            key = mg_Key_EQUALS;
            break;

        case SDLK_GREATER:
            key = mg_Key_GREATER;
            break;

        case SDLK_QUESTION:
            key = mg_Key_QUESTION;
            break;

        case SDLK_AT:
            key = mg_Key_AT;
            break;

        case SDLK_LEFTBRACKET:
            key = mg_Key_LEFTBRACKET;
            break;

        case SDLK_BACKSLASH:
            key = mg_Key_BACKSLASH;
            break;

        case SDLK_RIGHTBRACKET:
            key = mg_Key_RIGHTBRACKET;
            break;

        case SDLK_CARET:
            key = mg_Key_CARET;
            break;

        case SDLK_UNDERSCORE:
            key = mg_Key_UNDERSCORE;
            break;

        case SDLK_GRAVE:
            key = mg_Key_GRAVE;
            break;

        case SDLK_A:
            key = mg_Key_A;
            break;

        case SDLK_B:
            key = mg_Key_B;
            break;

        case SDLK_C:
            key = mg_Key_C;
            break;

        case SDLK_D:
            key = mg_Key_D;
            break;

        case SDLK_E:
            key = mg_Key_E;
            break;

        case SDLK_F:
            key = mg_Key_F;
            break;

        case SDLK_G:
            key = mg_Key_G;
            break;

        case SDLK_H:
            key = mg_Key_H;
            break;

        case SDLK_I:
            key = mg_Key_I;
            break;

        case SDLK_J:
            key = mg_Key_J;
            break;

        case SDLK_K:
            key = mg_Key_K;
            break;

        case SDLK_L:
            key = mg_Key_L;
            break;

        case SDLK_M:
            key = mg_Key_M;
            break;

        case SDLK_N:
            key = mg_Key_N;
            break;

        case SDLK_O:
            key = mg_Key_O;
            break;

        case SDLK_P:
            key = mg_Key_P;
            break;

        case SDLK_Q:
            key = mg_Key_Q;
            break;

        case SDLK_R:
            key = mg_Key_R;
            break;

        case SDLK_S:
            key = mg_Key_S;
            break;

        case SDLK_T:
            key = mg_Key_T;
            break;

        case SDLK_U:
            key = mg_Key_U;
            break;

        case SDLK_V:
            key = mg_Key_V;
            break;

        case SDLK_W:
            key = mg_Key_W;
            break;

        case SDLK_X:
            key = mg_Key_X;
            break;

        case SDLK_Y:
            key = mg_Key_Y;
            break;

        case SDLK_Z:
            key = mg_Key_Z;
            break;

        case SDLK_LEFTBRACE:
            key = mg_Key_LEFTBRACE;
            break;

        case SDLK_PIPE:
            key = mg_Key_PIPE;
            break;

        case SDLK_RIGHTBRACE:
            key = mg_Key_RIGHTBRACE;
            break;

        case SDLK_TILDE:
            key = mg_Key_TILDE;
            break;

        case SDLK_DELETE:
            key = mg_Key_DELETE;
            break;

        case SDLK_PLUSMINUS:
            key = mg_Key_PLUSMINUS;
            break;

        case SDLK_CAPSLOCK:
            key = mg_Key_CAPSLOCK;
            break;

        case SDLK_F1:
            key = mg_Key_F1;
            break;

        case SDLK_F2:
            key = mg_Key_F2;
            break;

        case SDLK_F3:
            key = mg_Key_F3;
            break;

        case SDLK_F4:
            key = mg_Key_F4;
            break;

        case SDLK_F5:
            key = mg_Key_F5;
            break;

        case SDLK_F6:
            key = mg_Key_F6;
            break;

        case SDLK_F7:
            key = mg_Key_F7;
            break;

        case SDLK_F8:
            key = mg_Key_F8;
            break;

        case SDLK_F9:
            key = mg_Key_F9;
            break;

        case SDLK_F10:
            key = mg_Key_F10;
            break;

        case SDLK_F11:
            key = mg_Key_F11;
            break;

        case SDLK_F12:
            key = mg_Key_F12;
            break;

        case SDLK_PRINTSCREEN:
            key = mg_Key_PRINTSCREEN;
            break;

        case SDLK_SCROLLLOCK:
            key = mg_Key_SCROLLLOCK;
            break;

        case SDLK_PAUSE:
            key = mg_Key_PAUSE;
            break;

        case SDLK_INSERT:
            key = mg_Key_INSERT;
            break;

        case SDLK_HOME:
            key = mg_Key_HOME;
            break;

        case SDLK_PAGEUP:
            key = mg_Key_PAGEUP;
            break;

        case SDLK_END:
            key = mg_Key_END;
            break;

        case SDLK_PAGEDOWN:
            key = mg_Key_PAGEDOWN;
            break;

        case SDLK_RIGHT:
            key = mg_Key_RIGHT;
            break;

        case SDLK_LEFT:
            key = mg_Key_LEFT;
            break;

        case SDLK_DOWN:
            key = mg_Key_DOWN;
            break;

        case SDLK_UP:
            key = mg_Key_UP;
            break;

        case SDLK_NUMLOCKCLEAR:
            key = mg_Key_NUMLOCKCLEAR;
            break;

        case SDLK_KP_DIVIDE:
            key = mg_Key_KP_DIVIDE;
            break;

        case SDLK_KP_MULTIPLY:
            key = mg_Key_KP_MULTIPLY;
            break;

        case SDLK_KP_MINUS:
            key = mg_Key_KP_MINUS;
            break;

        case SDLK_KP_PLUS:
            key = mg_Key_KP_PLUS;
            break;

        case SDLK_KP_ENTER:
            key = mg_Key_KP_ENTER;
            break;

        case SDLK_KP_1:
            key = mg_Key_KP_1;
            break;

        case SDLK_KP_2:
            key = mg_Key_KP_2;
            break;

        case SDLK_KP_3:
            key = mg_Key_KP_3;
            break;

        case SDLK_KP_4:
            key = mg_Key_KP_4;
            break;

        case SDLK_KP_5:
            key = mg_Key_KP_5;
            break;

        case SDLK_KP_6:
            key = mg_Key_KP_6;
            break;

        case SDLK_KP_7:
            key = mg_Key_KP_7;
            break;

        case SDLK_KP_8:
            key = mg_Key_KP_8;
            break;

        case SDLK_KP_9:
            key = mg_Key_KP_9;
            break;

        case SDLK_KP_0:
            key = mg_Key_KP_0;
            break;

        case SDLK_KP_PERIOD:
            key = mg_Key_KP_PERIOD;
            break;

        case SDLK_APPLICATION:
            key = mg_Key_APPLICATION;
            break;

        case SDLK_POWER:
            key = mg_Key_POWER;
            break;

        case SDLK_KP_EQUALS:
            key = mg_Key_KP_EQUALS;
            break;

        case SDLK_F13:
            key = mg_Key_F13;
            break;

        case SDLK_F14:
            key = mg_Key_F14;
            break;

        case SDLK_F15:
            key = mg_Key_F15;
            break;

        case SDLK_F16:
            key = mg_Key_F16;
            break;

        case SDLK_F17:
            key = mg_Key_F17;
            break;

        case SDLK_F18:
            key = mg_Key_F18;
            break;

        case SDLK_F19:
            key = mg_Key_F19;
            break;

        case SDLK_F20:
            key = mg_Key_F20;
            break;

        case SDLK_F21:
            key = mg_Key_F21;
            break;

        case SDLK_F22:
            key = mg_Key_F22;
            break;

        case SDLK_F23:
            key = mg_Key_F23;
            break;

        case SDLK_F24:
            key = mg_Key_F24;
            break;

        case SDLK_EXECUTE:
            key = mg_Key_EXECUTE;
            break;

        case SDLK_HELP:
            key = mg_Key_HELP;
            break;

        case SDLK_MENU:
            key = mg_Key_MENU;
            break;

        case SDLK_SELECT:
            key = mg_Key_SELECT;
            break;

        case SDLK_STOP:
            key = mg_Key_STOP;
            break;

        case SDLK_AGAIN:
            key = mg_Key_AGAIN;
            break;

        case SDLK_UNDO:
            key = mg_Key_UNDO;
            break;

        case SDLK_CUT:
            key = mg_Key_CUT;
            break;

        case SDLK_COPY:
            key = mg_Key_COPY;
            break;

        case SDLK_PASTE:
            key = mg_Key_PASTE;
            break;

        case SDLK_FIND:
            key = mg_Key_FIND;
            break;

        case SDLK_MUTE:
            key = mg_Key_MUTE;
            break;

        case SDLK_VOLUMEUP:
            key = mg_Key_VOLUMEUP;
            break;

        case SDLK_VOLUMEDOWN:
            key = mg_Key_VOLUMEDOWN;
            break;

        case SDLK_KP_COMMA:
            key = mg_Key_KP_COMMA;
            break;

        case SDLK_KP_EQUALSAS400:
            key = mg_Key_KP_EQUALSAS400;
            break;

        case SDLK_ALTERASE:
            key = mg_Key_ALTERASE;
            break;

        case SDLK_SYSREQ:
            key = mg_Key_SYSREQ;
            break;

        case SDLK_CANCEL:
            key = mg_Key_CANCEL;
            break;

        case SDLK_CLEAR:
            key = mg_Key_CLEAR;
            break;

        case SDLK_PRIOR:
            key = mg_Key_PRIOR;
            break;

        case SDLK_RETURN2:
            key = mg_Key_RETURN2;
            break;

        case SDLK_SEPARATOR:
            key = mg_Key_SEPARATOR;
            break;

        case SDLK_OUT:
            key = mg_Key_OUT;
            break;

        case SDLK_OPER:
            key = mg_Key_OPER;
            break;

        case SDLK_CLEARAGAIN:
            key = mg_Key_CLEARAGAIN;
            break;

        case SDLK_CRSEL:
            key = mg_Key_CRSEL;
            break;

        case SDLK_EXSEL:
            key = mg_Key_EXSEL;
            break;

        case SDLK_KP_00:
            key = mg_Key_KP_00;
            break;

        case SDLK_KP_000:
            key = mg_Key_KP_000;
            break;

        case SDLK_THOUSANDSSEPARATOR:
            key = mg_Key_THOUSANDSSEPARATOR;
            break;

        case SDLK_DECIMALSEPARATOR:
            key = mg_Key_DECIMALSEPARATOR;
            break;

        case SDLK_CURRENCYUNIT:
            key = mg_Key_CURRENCYUNIT;
            break;

        case SDLK_CURRENCYSUBUNIT:
            key = mg_Key_CURRENCYSUBUNIT;
            break;

        case SDLK_KP_LEFTPAREN:
            key = mg_Key_KP_LEFTPAREN;
            break;

        case SDLK_KP_RIGHTPAREN:
            key = mg_Key_KP_RIGHTPAREN;
            break;

        case SDLK_KP_LEFTBRACE:
            key = mg_Key_KP_LEFTBRACE;
            break;

        case SDLK_KP_RIGHTBRACE:
            key = mg_Key_KP_RIGHTBRACE;
            break;

        case SDLK_KP_TAB:
            key = mg_Key_KP_TAB;
            break;

        case SDLK_KP_BACKSPACE:
            key = mg_Key_KP_BACKSPACE;
            break;

        case SDLK_KP_A:
            key = mg_Key_KP_A;
            break;

        case SDLK_KP_B:
            key = mg_Key_KP_B;
            break;

        case SDLK_KP_C:
            key = mg_Key_KP_C;
            break;

        case SDLK_KP_D:
            key = mg_Key_KP_D;
            break;

        case SDLK_KP_E:
            key = mg_Key_KP_E;
            break;

        case SDLK_KP_F:
            key = mg_Key_KP_F;
            break;

        case SDLK_KP_XOR:
            key = mg_Key_KP_XOR;
            break;

        case SDLK_KP_POWER:
            key = mg_Key_KP_POWER;
            break;

        case SDLK_KP_PERCENT:
            key = mg_Key_KP_PERCENT;
            break;

        case SDLK_KP_LESS:
            key = mg_Key_KP_LESS;
            break;

        case SDLK_KP_GREATER:
            key = mg_Key_KP_GREATER;
            break;

        case SDLK_KP_AMPERSAND:
            key = mg_Key_KP_AMPERSAND;
            break;

        case SDLK_KP_DBLAMPERSAND:
            key = mg_Key_KP_DBLAMPERSAND;
            break;

        case SDLK_KP_VERTICALBAR:
            key = mg_Key_KP_VERTICALBAR;
            break;

        case SDLK_KP_DBLVERTICALBAR:
            key = mg_Key_KP_DBLVERTICALBAR;
            break;

        case SDLK_KP_COLON:
            key = mg_Key_KP_COLON;
            break;

        case SDLK_KP_HASH:
            key = mg_Key_KP_HASH;
            break;

        case SDLK_KP_SPACE:
            key = mg_Key_KP_SPACE;
            break;

        case SDLK_KP_AT:
            key = mg_Key_KP_AT;
            break;

        case SDLK_KP_EXCLAM:
            key = mg_Key_KP_EXCLAM;
            break;

        case SDLK_KP_MEMSTORE:
            key = mg_Key_KP_MEMSTORE;
            break;

        case SDLK_KP_MEMRECALL:
            key = mg_Key_KP_MEMRECALL;
            break;

        case SDLK_KP_MEMCLEAR:
            key = mg_Key_KP_MEMCLEAR;
            break;

        case SDLK_KP_MEMADD:
            key = mg_Key_KP_MEMADD;
            break;

        case SDLK_KP_MEMSUBTRACT:
            key = mg_Key_KP_MEMSUBTRACT;
            break;

        case SDLK_KP_MEMMULTIPLY:
            key = mg_Key_KP_MEMMULTIPLY;
            break;

        case SDLK_KP_MEMDIVIDE:
            key = mg_Key_KP_MEMDIVIDE;
            break;

        case SDLK_KP_PLUSMINUS:
            key = mg_Key_KP_PLUSMINUS;
            break;

        case SDLK_KP_CLEAR:
            key = mg_Key_KP_CLEAR;
            break;

        case SDLK_KP_CLEARENTRY:
            key = mg_Key_KP_CLEARENTRY;
            break;

        case SDLK_KP_BINARY:
            key = mg_Key_KP_BINARY;
            break;

        case SDLK_KP_OCTAL:
            key = mg_Key_KP_OCTAL;
            break;

        case SDLK_KP_DECIMAL:
            key = mg_Key_KP_DECIMAL;
            break;

        case SDLK_KP_HEXADECIMAL:
            key = mg_Key_KP_HEXADECIMAL;
            break;

        case SDLK_LCTRL:
            key = mg_Key_LCTRL;
            break;

        case SDLK_LSHIFT:
            key = mg_Key_LSHIFT;
            break;

        case SDLK_LALT:
            key = mg_Key_LALT;
            break;

        case SDLK_LGUI:
            key = mg_Key_LGUI;
            break;

        case SDLK_RCTRL:
            key = mg_Key_RCTRL;
            break;

        case SDLK_RSHIFT:
            key = mg_Key_RSHIFT;
            break;

        case SDLK_RALT:
            key = mg_Key_RALT;
            break;

        case SDLK_RGUI:
            key = mg_Key_RGUI;
            break;

        case SDLK_MODE:
            key = mg_Key_MODE;
            break;

        case SDLK_SLEEP:
            key = mg_Key_SLEEP;
            break;

        case SDLK_WAKE:
            key = mg_Key_WAKE;
            break;

        case SDLK_CHANNEL_INCREMENT:
            key = mg_Key_CHANNEL_INCREMENT;
            break;

        case SDLK_CHANNEL_DECREMENT:
            key = mg_Key_CHANNEL_DECREMENT;
            break;

        case SDLK_MEDIA_PLAY:
            key = mg_Key_MEDIA_PLAY;
            break;

        case SDLK_MEDIA_PAUSE:
            key = mg_Key_MEDIA_PAUSE;
            break;

        case SDLK_MEDIA_RECORD:
            key = mg_Key_MEDIA_RECORD;
            break;

        case SDLK_MEDIA_FAST_FORWARD:
            key = mg_Key_MEDIA_FAST_FORWARD;
            break;

        case SDLK_MEDIA_REWIND:
            key = mg_Key_MEDIA_REWIND;
            break;

        case SDLK_MEDIA_NEXT_TRACK:
            key = mg_Key_MEDIA_NEXT_TRACK;
            break;

        case SDLK_MEDIA_PREVIOUS_TRACK:
            key = mg_Key_MEDIA_PREVIOUS_TRACK;
            break;

        case SDLK_MEDIA_STOP:
            key = mg_Key_MEDIA_STOP;
            break;

        case SDLK_MEDIA_EJECT:
            key = mg_Key_MEDIA_EJECT;
            break;

        case SDLK_MEDIA_PLAY_PAUSE:
            key = mg_Key_MEDIA_PLAY_PAUSE;
            break;

        case SDLK_MEDIA_SELECT:
            key = mg_Key_MEDIA_SELECT;
            break;

        case SDLK_AC_NEW:
            key = mg_Key_AC_NEW;
            break;

        case SDLK_AC_OPEN:
            key = mg_Key_AC_OPEN;
            break;

        case SDLK_AC_CLOSE:
            key = mg_Key_AC_CLOSE;
            break;

        case SDLK_AC_EXIT:
            key = mg_Key_AC_EXIT;
            break;

        case SDLK_AC_SAVE:
            key = mg_Key_AC_SAVE;
            break;

        case SDLK_AC_PRINT:
            key = mg_Key_AC_PRINT;
            break;

        case SDLK_AC_PROPERTIES:
            key = mg_Key_AC_PROPERTIES;
            break;

        case SDLK_AC_SEARCH:
            key = mg_Key_AC_SEARCH;
            break;

        case SDLK_AC_HOME:
            key = mg_Key_AC_HOME;
            break;

        case SDLK_AC_BACK:
            key = mg_Key_AC_BACK;
            break;

        case SDLK_AC_FORWARD:
            key = mg_Key_AC_FORWARD;
            break;

        case SDLK_AC_STOP:
            key = mg_Key_AC_STOP;
            break;

        case SDLK_AC_REFRESH:
            key = mg_Key_AC_REFRESH;
            break;

        case SDLK_AC_BOOKMARKS:
            key = mg_Key_AC_BOOKMARKS;
            break;

        case SDLK_SOFTLEFT:
            key = mg_Key_SOFTLEFT;
            break;

        case SDLK_SOFTRIGHT:
            key = mg_Key_SOFTRIGHT;
            break;

        case SDLK_CALL:
            key = mg_Key_CALL;
            break;

        case SDLK_ENDCALL:
            key = mg_Key_ENDCALL;
            break;

        case SDLK_LEFT_TAB:
            key = mg_Key_LEFT_TAB;
            break;

        case SDLK_LEVEL5_SHIFT:
            key = mg_Key_LEVEL5_SHIFT;
            break;

        case SDLK_MULTI_KEY_COMPOSE:
            key = mg_Key_MULTI_KEY_COMPOSE;
            break;

        case SDLK_LMETA:
            key = mg_Key_LMETA;
            break;

        case SDLK_RMETA:
            key = mg_Key_RMETA;
            break;

        case SDLK_LHYPER:
            key = mg_Key_LHYPER;
            break;

        case SDLK_RHYPER:
            key = mg_Key_RHYPER;
            break;
    }

    mg_Event mgEvent = {
        .key = {.type = mg_EventType_KEY, .key = key, .action = action}};

    mg_event_push(context->event_context, &mgEvent);
}

mg_Texture *mg_texture_load(mg_WindowContext *context, const char *path) {
    assert(context != NULL);
    assert(context->renderer != NULL);
    assert(path != NULL);

    SDL_Texture *sdl_texture = IMG_LoadTexture(context->renderer, path);
    if (sdl_texture == NULL) {
        mg_LOG_ERROR("%s\n", SDL_GetError());
        return NULL;
    }

    mg_Texture *texture = malloc(sizeof(mg_Texture));
    if (texture == NULL) {
        SDL_DestroyTexture(sdl_texture);
        mg_LOG_ERROR("Failed to allocate memory for texture");
        return NULL;
    }

    texture->sdl_texture = sdl_texture;

    if (!SDL_GetTextureSize(texture->sdl_texture, &texture->size.x,
                            &texture->size.y)) {
        SDL_DestroyTexture(sdl_texture);
        free(texture);

        mg_LOG_ERROR("%s", SDL_GetError());

        return NULL;
    }

    return texture;
}

void mg_texture_free(mg_Texture *texture) {
    assert(texture != NULL);
    assert(texture->sdl_texture != NULL);

    SDL_DestroyTexture(texture->sdl_texture);
    free(texture);
}

mg_Vec2f mg_texture_get_size(mg_Texture *texture) { return texture->size; }

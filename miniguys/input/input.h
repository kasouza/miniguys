#ifndef KASOUZA_MINIGUYS_INPUT_INPUT_H
#define KASOUZA_MINIGUYS_INPUT_INPUT_H

#include <stdbool.h>
typedef struct mg_key_event_t mg_KeyEvent;
typedef struct mg_window_context_t mg_WindowContext;

typedef enum mg_key_t {
    mg_Key_FIRST = 0,
    mg_Key_UNKNOWN,
    mg_Key_RETURN,
    mg_Key_ESCAPE,
    mg_Key_BACKSPACE,
    mg_Key_TAB,
    mg_Key_SPACE,
    mg_Key_EXCLAIM,
    mg_Key_DBLAPOSTROPHE,
    mg_Key_HASH,
    mg_Key_DOLLAR,
    mg_Key_PERCENT,
    mg_Key_AMPERSAND,
    mg_Key_APOSTROPHE,
    mg_Key_LEFTPAREN,
    mg_Key_RIGHTPAREN,
    mg_Key_ASTERISK,
    mg_Key_PLUS,
    mg_Key_COMMA,
    mg_Key_MINUS,
    mg_Key_PERIOD,
    mg_Key_SLASH,
    mg_Key_0,
    mg_Key_1,
    mg_Key_2,
    mg_Key_3,
    mg_Key_4,
    mg_Key_5,
    mg_Key_6,
    mg_Key_7,
    mg_Key_8,
    mg_Key_9,
    mg_Key_COLON,
    mg_Key_SEMICOLON,
    mg_Key_LESS,
    mg_Key_EQUALS,
    mg_Key_GREATER,
    mg_Key_QUESTION,
    mg_Key_AT,
    mg_Key_LEFTBRACKET,
    mg_Key_BACKSLASH,
    mg_Key_RIGHTBRACKET,
    mg_Key_CARET,
    mg_Key_UNDERSCORE,
    mg_Key_GRAVE,
    mg_Key_A,
    mg_Key_B,
    mg_Key_C,
    mg_Key_D,
    mg_Key_E,
    mg_Key_F,
    mg_Key_G,
    mg_Key_H,
    mg_Key_I,
    mg_Key_J,
    mg_Key_K,
    mg_Key_L,
    mg_Key_M,
    mg_Key_N,
    mg_Key_O,
    mg_Key_P,
    mg_Key_Q,
    mg_Key_R,
    mg_Key_S,
    mg_Key_T,
    mg_Key_U,
    mg_Key_V,
    mg_Key_W,
    mg_Key_X,
    mg_Key_Y,
    mg_Key_Z,
    mg_Key_LEFTBRACE,
    mg_Key_PIPE,
    mg_Key_RIGHTBRACE,
    mg_Key_TILDE,
    mg_Key_DELETE,
    mg_Key_PLUSMINUS,
    mg_Key_CAPSLOCK,
    mg_Key_F1,
    mg_Key_F2,
    mg_Key_F3,
    mg_Key_F4,
    mg_Key_F5,
    mg_Key_F6,
    mg_Key_F7,
    mg_Key_F8,
    mg_Key_F9,
    mg_Key_F10,
    mg_Key_F11,
    mg_Key_F12,
    mg_Key_PRINTSCREEN,
    mg_Key_SCROLLLOCK,
    mg_Key_PAUSE,
    mg_Key_INSERT,
    mg_Key_HOME,
    mg_Key_PAGEUP,
    mg_Key_END,
    mg_Key_PAGEDOWN,
    mg_Key_RIGHT,
    mg_Key_LEFT,
    mg_Key_DOWN,
    mg_Key_UP,
    mg_Key_NUMLOCKCLEAR,
    mg_Key_KP_DIVIDE,
    mg_Key_KP_MULTIPLY,
    mg_Key_KP_MINUS,
    mg_Key_KP_PLUS,
    mg_Key_KP_ENTER,
    mg_Key_KP_1,
    mg_Key_KP_2,
    mg_Key_KP_3,
    mg_Key_KP_4,
    mg_Key_KP_5,
    mg_Key_KP_6,
    mg_Key_KP_7,
    mg_Key_KP_8,
    mg_Key_KP_9,
    mg_Key_KP_0,
    mg_Key_KP_PERIOD,
    mg_Key_APPLICATION,
    mg_Key_POWER,
    mg_Key_KP_EQUALS,
    mg_Key_F13,
    mg_Key_F14,
    mg_Key_F15,
    mg_Key_F16,
    mg_Key_F17,
    mg_Key_F18,
    mg_Key_F19,
    mg_Key_F20,
    mg_Key_F21,
    mg_Key_F22,
    mg_Key_F23,
    mg_Key_F24,
    mg_Key_EXECUTE,
    mg_Key_HELP,
    mg_Key_MENU,
    mg_Key_SELECT,
    mg_Key_STOP,
    mg_Key_AGAIN,
    mg_Key_UNDO,
    mg_Key_CUT,
    mg_Key_COPY,
    mg_Key_PASTE,
    mg_Key_FIND,
    mg_Key_MUTE,
    mg_Key_VOLUMEUP,
    mg_Key_VOLUMEDOWN,
    mg_Key_KP_COMMA,
    mg_Key_KP_EQUALSAS400,
    mg_Key_ALTERASE,
    mg_Key_SYSREQ,
    mg_Key_CANCEL,
    mg_Key_CLEAR,
    mg_Key_PRIOR,
    mg_Key_RETURN2,
    mg_Key_SEPARATOR,
    mg_Key_OUT,
    mg_Key_OPER,
    mg_Key_CLEARAGAIN,
    mg_Key_CRSEL,
    mg_Key_EXSEL,
    mg_Key_KP_00,
    mg_Key_KP_000,
    mg_Key_THOUSANDSSEPARATOR,
    mg_Key_DECIMALSEPARATOR,
    mg_Key_CURRENCYUNIT,
    mg_Key_CURRENCYSUBUNIT,
    mg_Key_KP_LEFTPAREN,
    mg_Key_KP_RIGHTPAREN,
    mg_Key_KP_LEFTBRACE,
    mg_Key_KP_RIGHTBRACE,
    mg_Key_KP_TAB,
    mg_Key_KP_BACKSPACE,
    mg_Key_KP_A,
    mg_Key_KP_B,
    mg_Key_KP_C,
    mg_Key_KP_D,
    mg_Key_KP_E,
    mg_Key_KP_F,
    mg_Key_KP_XOR,
    mg_Key_KP_POWER,
    mg_Key_KP_PERCENT,
    mg_Key_KP_LESS,
    mg_Key_KP_GREATER,
    mg_Key_KP_AMPERSAND,
    mg_Key_KP_DBLAMPERSAND,
    mg_Key_KP_VERTICALBAR,
    mg_Key_KP_DBLVERTICALBAR,
    mg_Key_KP_COLON,
    mg_Key_KP_HASH,
    mg_Key_KP_SPACE,
    mg_Key_KP_AT,
    mg_Key_KP_EXCLAM,
    mg_Key_KP_MEMSTORE,
    mg_Key_KP_MEMRECALL,
    mg_Key_KP_MEMCLEAR,
    mg_Key_KP_MEMADD,
    mg_Key_KP_MEMSUBTRACT,
    mg_Key_KP_MEMMULTIPLY,
    mg_Key_KP_MEMDIVIDE,
    mg_Key_KP_PLUSMINUS,
    mg_Key_KP_CLEAR,
    mg_Key_KP_CLEARENTRY,
    mg_Key_KP_BINARY,
    mg_Key_KP_OCTAL,
    mg_Key_KP_DECIMAL,
    mg_Key_KP_HEXADECIMAL,
    mg_Key_LCTRL,
    mg_Key_LSHIFT,
    mg_Key_LALT,
    mg_Key_LGUI,
    mg_Key_RCTRL,
    mg_Key_RSHIFT,
    mg_Key_RALT,
    mg_Key_RGUI,
    mg_Key_MODE,
    mg_Key_SLEEP,
    mg_Key_WAKE,
    mg_Key_CHANNEL_INCREMENT,
    mg_Key_CHANNEL_DECREMENT,
    mg_Key_MEDIA_PLAY,
    mg_Key_MEDIA_PAUSE,
    mg_Key_MEDIA_RECORD,
    mg_Key_MEDIA_FAST_FORWARD,
    mg_Key_MEDIA_REWIND,
    mg_Key_MEDIA_NEXT_TRACK,
    mg_Key_MEDIA_PREVIOUS_TRACK,
    mg_Key_MEDIA_STOP,
    mg_Key_MEDIA_EJECT,
    mg_Key_MEDIA_PLAY_PAUSE,
    mg_Key_MEDIA_SELECT,
    mg_Key_AC_NEW,
    mg_Key_AC_OPEN,
    mg_Key_AC_CLOSE,
    mg_Key_AC_EXIT,
    mg_Key_AC_SAVE,
    mg_Key_AC_PRINT,
    mg_Key_AC_PROPERTIES,
    mg_Key_AC_SEARCH,
    mg_Key_AC_HOME,
    mg_Key_AC_BACK,
    mg_Key_AC_FORWARD,
    mg_Key_AC_STOP,
    mg_Key_AC_REFRESH,
    mg_Key_AC_BOOKMARKS,
    mg_Key_SOFTLEFT,
    mg_Key_SOFTRIGHT,
    mg_Key_CALL,
    mg_Key_ENDCALL,
    mg_Key_LEFT_TAB,
    mg_Key_LEVEL5_SHIFT,
    mg_Key_MULTI_KEY_COMPOSE,
    mg_Key_LMETA,
    mg_Key_RMETA,
    mg_Key_LHYPER,
    mg_Key_RHYPER,
    mg_Key_LAST
} mg_Key;

typedef enum mg_action_t {
    mg_Action_RELEASE = 0,
    mg_Action_PRESS = 1,
    mg_Action_REPEAT = 2
} mg_Action;

typedef struct mg_input_context_t {
    bool pressed[mg_Key_LAST];
} mg_InputContext;

mg_InputContext *mg_input_init();
void mg_input_handle_key_event(mg_InputContext *context, mg_KeyEvent *event);
bool mg_input_is_key_pressed(mg_InputContext *context, mg_Key key);
void mg_input_terminate(mg_InputContext *context);

#endif

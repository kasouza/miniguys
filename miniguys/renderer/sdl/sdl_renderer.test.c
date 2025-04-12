#include "sdl_renderer.test.h"
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/test.h"

#include <stdbool.h>
#include <unistd.h>

mg_EventContext *event_context;
mg_WindowContext *window_context;

static void before_all() {
    event_context = mg_event_init();
    assert(event_context != NULL);

    window_context = mg_renderer_init(event_context);
    assert(window_context != NULL);
}

static void after_all() {
    mg_event_terminate(event_context);
    mg_renderer_terminate(window_context);
}

static bool test_texture() {
    mg_Texture *texture =
        mg_texture_load(window_context, "assets/test/amogus.png");
    t_ASSERT_NOT_NULL(texture);
    mg_texture_free(texture);

    mg_Texture *should_be_null =
        mg_texture_load(window_context, "assets/test/invalid.png");
    t_ASSERT_NULL(should_be_null);

    return true;
}

void mg_testsuite_sdl_renderer() {
    t_TESTSUITE("sdl_renderer", before_all, after_all);

    t_TS_TEST("sdl_renderer", test_texture);
}

#include "sdl_renderer.test.h"
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sprite.h"
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
    // Regular texture
    mg_Texture *texture =
        mg_texture_load(window_context, "assets/test/amogus.png");
    t_ASSERT_NOT_NULL(texture);
    mg_texture_free(texture);
    texture = NULL;

    // Non-existing texture
    mg_Texture *should_be_null =
        mg_texture_load(window_context, "assets/test/invalid.png");
    t_ASSERT_NULL(should_be_null);

    // Fixed size texture to check size
    mg_Texture *fixed_size = mg_texture_load(window_context, "assets/test/amogus_32x32.png");
    t_ASSERT_NOT_NULL(fixed_size);

    mg_Vec2f size = mg_texture_get_size(fixed_size);
    t_ASSERT_EQ(size.x, 32);
    t_ASSERT_EQ(size.y, 32);

    mg_texture_free(fixed_size);
    fixed_size = NULL;

    return true;
}

void mg_testsuite_sdl_renderer() {
    t_TESTSUITE("sdl_renderer", before_all, after_all);

    t_TS_TEST("sdl_renderer", test_texture);
}

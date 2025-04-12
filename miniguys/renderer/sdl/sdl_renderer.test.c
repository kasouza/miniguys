#include "sdl_renderer.test.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sprite.h"
#include "miniguys/test.h"

#include <stdbool.h>
#include <unistd.h>

static mg_WindowContext *s_window_context;

static bool test_texture() {
    // Regular texture
    mg_Texture *texture =
        mg_texture_load(s_window_context, "assets/test/amogus.png");
    t_ASSERT_NOT_NULL(texture);
    mg_texture_free(texture);
    texture = NULL;

    // Non-existing texture
    mg_Texture *should_be_null =
        mg_texture_load(s_window_context, "assets/test/invalid.png");
    t_ASSERT_NULL(should_be_null);

    // Fixed size texture to check size
    mg_Texture *fixed_size = mg_texture_load(s_window_context, "assets/test/amogus_32x32.png");
    t_ASSERT_NOT_NULL(fixed_size);

    mg_Vec2f size = mg_texture_get_size(fixed_size);
    t_ASSERT_EQ(size.x, 32);
    t_ASSERT_EQ(size.y, 32);

    mg_texture_free(fixed_size);
    fixed_size = NULL;

    return true;
}

void mg_testsuite_sdl_renderer(mg_WindowContext *window_context) {
    assert(window_context != NULL);
    s_window_context = window_context;

    t_TESTSUITE("sdl_renderer", NULL, NULL);

    t_TS_TEST("sdl_renderer", test_texture);
}

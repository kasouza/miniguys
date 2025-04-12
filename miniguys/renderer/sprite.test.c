#include "miniguys/renderer/sprite.test.h"

#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/math/vec2f.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sprite.h"
#include "miniguys/test.h"

#include <stdbool.h>
#include <unistd.h>

static mg_WindowContext *s_window_context;

static bool test_sprite() {
    // Regular sprite
    mg_Sprite *sprite =
        mg_sprite_load(s_window_context, "assets/test/amogus.png");
    t_ASSERT_NOT_NULL(sprite);
    mg_sprite_free(sprite);
    sprite = NULL;

    /*// Non-existing sprite*/
    mg_Sprite *should_be_null =
        mg_sprite_load(s_window_context, "assets/test/invalid.png");
    t_ASSERT_NULL(should_be_null);

    // Fixed size sprite to check size
    mg_Sprite *fixed_size = mg_sprite_load(s_window_context, "assets/test/amogus_32x32.png");
    t_ASSERT_NOT_NULL(fixed_size);

    t_ASSERT_EQ(fixed_size->size.x, 32);
    t_ASSERT_EQ(fixed_size->size.y, 32);

    mg_sprite_free(fixed_size);
    fixed_size = NULL;

    return true;
}

void mg_testsuite_sprite(mg_WindowContext *window_context) {
    assert(window_context != NULL);
    s_window_context = window_context;
    
    t_TESTSUITE("sprite", NULL, NULL);

    t_TS_TEST("sprite", test_sprite);
}

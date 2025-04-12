#include "miniguys/debug.h"
#include "miniguys/event/event.h"
#include "miniguys/input/input.h"
#include "miniguys/renderer/renderer.h"
#include "miniguys/renderer/sdl/sdl_renderer.test.h"
#include "miniguys/renderer/sprite.test.h"

#define MAX_TESTS 1
#define KASOUZA_TEST_IMPL

#include "test.h"

bool test_test() {
    t_ASSERT(1 == 1);

    return true;
}

int main() {
    mg_EventContext *event_context = mg_event_init();
    assert(event_context != NULL);

    mg_WindowContext *window_context = mg_renderer_init(event_context);
    assert(window_context != NULL);
    mg_should_log(false);


    t_TEST(test_test);
    mg_testsuite_sdl_renderer(window_context);
    mg_testsuite_sprite(window_context);

    t_run_tests();

    mg_renderer_terminate(window_context);
    mg_event_terminate(event_context);

    return 0;
}

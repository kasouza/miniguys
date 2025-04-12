#include "miniguys/renderer/sdl/sdl_renderer.test.h"
#define MAX_TESTS 1
#define KASOUZA_TEST_IMPL

#include "test.h"

bool test_test() {
    t_ASSERT(1 == 1);

    return true;
}

int main() {
    t_REGISTER_TEST(test_test);
    testsuite_sdl_renderer();

    t_run_tests();

    return 0;
}

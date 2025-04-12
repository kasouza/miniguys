#ifndef KASOUZA_MG_TEST_H
#define KASOUZA_MG_TEST_H

/* == Configurations == */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#ifndef MAX_TESTS
#define MAX_TESTS 32
#endif

#define T_GLOBAL_TESTSUITE_NAME "__GLOBAL_TEST_SUITE__"

/* ==================== */

/* === Header stuff === */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h> // IWYU pragma: keep

typedef bool (*t_test_func)();
typedef void (*t_before_all_func_t)();
typedef void (*t_after_all_func_t)();

typedef struct {
    const char *name;
    t_test_func test;
} t_Test;

typedef struct {
    const char *name;
    t_before_all_func_t before_all;
    t_after_all_func_t after_all;

    t_Test *tests;
    int tests_len;
    int tests_cap;
} t_TestSuite;

#define t_TEST(test) t_register_named_test(#test, test, NULL)
#define t_TS_TEST(testsuite, test) t_register_named_test(#test, test, testsuite)
#define t_TESTSUITE(ts_name, _before_all, _after_all) t_register_testsuite((t_TestSuite){ .name=ts_name, .before_all = _before_all, .after_all = _after_all })

#define t_ASSERT(condition)                                                    \
    do {                                                                       \
        if (!(condition)) {                                                    \
            printf("\x1B[31mFAILED\x1B[0m [%s, %d] - %s\n", __FILE__,          \
                   __LINE__, #condition);                                      \
            return false;                                                      \
        }                                                                      \
    } while (0)

void t_register_named_test(const char *name, t_test_func test,
                           const char *testsuite_name);
void t_register_testsuite(t_TestSuite testsuite);
void t_run_tests();

/* ==================== */

/* == Implementation == */
#ifdef KASOUZA_TEST_IMPL
static size_t total_tests_count = 0;

static t_TestSuite *testsuites;
static int testsuites_len;
static int testsuites_cap;

void t_init_testsuites() {
    testsuites_len = 0;
    testsuites_cap = 8;
    testsuites = calloc(testsuites_cap, sizeof(t_TestSuite));
    assert(testsuites != NULL);

    t_register_testsuite((t_TestSuite){.name = T_GLOBAL_TESTSUITE_NAME});
}

void t_register_named_test(const char *name, t_test_func test,
                           const char *testsuite_name) {
    t_TestSuite *testsuite = NULL;

    if (testsuite_name == NULL) {
        if (testsuites == NULL) {
            t_init_testsuites();
        }

        testsuite = &testsuites[0];
    } else {
        for (int i = 0; i < testsuites_len; i++) {
            if (strcmp(testsuites[i].name, testsuite_name) == 0) {
                testsuite = &testsuites[i];
            }
        }
    }

    if (testsuite == NULL) {
        fprintf(stderr, "Test suite %s not found\n", testsuite_name);
        exit(1);
    }

    if (testsuite->tests_len >= testsuite->tests_cap) {
        testsuite->tests_cap *= 2;
        testsuite->tests =
            realloc(testsuite->tests, testsuite->tests_cap * sizeof(t_Test));
        assert(testsuite->tests != NULL);
    }

    int idx = testsuite->tests_len;
    testsuite->tests[idx].name = name;
    testsuite->tests[idx].test = test;

    testsuite->tests_len++;
    total_tests_count++;
}

void t_register_testsuite(t_TestSuite testsuite) {
    assert(testsuite.name != NULL);

    for (int i = 0; i < testsuites_len; i++) {
        if (strcmp(testsuite.name, testsuites[i].name) == 0) {
            fprintf(stderr, "Test suite %s already exists\n", testsuite.name);
            exit(1);
        }
    }

    if (testsuites_len >= testsuites_cap) {
        testsuites_cap *= 2;
        testsuites = realloc(testsuites, testsuites_cap * sizeof(t_TestSuite));
        assert(testsuites != NULL);
    }

    if (testsuite.tests == NULL) {
        testsuite.tests_cap = 8;
        testsuite.tests_len = 0;
        testsuite.tests = malloc(testsuite.tests_cap * sizeof(t_Test));
        assert(testsuite.tests != NULL);
    }

    testsuites[testsuites_len] = testsuite;
    testsuites_len++;
}

void t_run_tests() {
    printf("Total tests: %ld\n\n", total_tests_count);
    int failed = 0;

    for (size_t testsuite_idx = 0; testsuite_idx < testsuites_len;
         testsuite_idx++) {

        t_TestSuite *testsuite = &testsuites[testsuite_idx];
        printf("\x1B[34mTESTSUITE: %s\x1B[0m\n", testsuite->name);

        if (testsuite->before_all) {
            testsuite->before_all();
        }

        for (size_t test_idx = 0; test_idx < testsuite->tests_len; test_idx++) {
            bool result = testsuite->tests[test_idx].test();

            if (!result) {
                printf("\x1B[31m    - IN TEST:\x1B[0m %s\n",
                       testsuite->tests[test_idx].name);
                failed++;
            } else {
                printf("\x1B[32mSUCCESS: %s\x1B[0m\n",
                       testsuite->tests[test_idx].name);
            }
        }

        if (testsuite->after_all) {
            testsuite->after_all();
        }

        printf("\n");
    }

    int sucessfull = total_tests_count - failed;
    printf("\nFINISHED \x1B[32m%d sucessfull \x1B[0mand \x1B[31m%d "
           "failed\x1B[0m\n",
           sucessfull, failed);
}
#endif
/* ==================== */

#endif

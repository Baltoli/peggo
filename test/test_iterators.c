#include <stdlib.h>
#include <string.h>

#include "test_iterator.h"

static int setup(void **state) {
  return 0;
}

static int teardown(void **state) {
  return 0;
}

const struct CMUnitTest iterator_tests[] = {
};

int test_iterators(void) {
  return cmocka_run_group_tests(iterator_tests, setup, teardown);
}

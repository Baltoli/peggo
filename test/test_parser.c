#include <stdlib.h>
#include <string.h>

#include "test_parser.h"
#include "test_parser_p.h"

static int setup(void **state) {
  return 0;
}

static int teardown(void **state) {
  return 0;
}

const struct CMUnitTest parser_tests[] = {
  cmocka_unit_test(empty_success),
  cmocka_unit_test(terminal_success),
  cmocka_unit_test(terminal_failure),
  cmocka_unit_test(non_terminal_success),
  cmocka_unit_test(non_terminal_failure),
};

int test_parser(void) {
  return cmocka_run_group_tests(parser_tests, setup, teardown);
}

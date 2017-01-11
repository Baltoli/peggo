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

  cmocka_unit_test(sequence_success),
  cmocka_unit_test(sequence_failure),
  cmocka_unit_test(sequence_first),
  cmocka_unit_test(sequence_second),

  cmocka_unit_test(choice_first),
  cmocka_unit_test(choice_second),
  cmocka_unit_test(choice_longer),
  cmocka_unit_test(choice_failure),

  cmocka_unit_test(zero_or_more_zero),
  cmocka_unit_test(zero_or_more_one),
  cmocka_unit_test(zero_or_more_many),

  cmocka_unit_test(one_or_more_one),
  cmocka_unit_test(one_or_more_many),
  cmocka_unit_test(one_or_more_failure),

  cmocka_unit_test(optional_some),
  cmocka_unit_test(optional_none),

  cmocka_unit_test(and_true),
  cmocka_unit_test(and_false),

  cmocka_unit_test(not_true),
  cmocka_unit_test(not_false),
};

int test_parser(void) {
  return cmocka_run_group_tests(parser_tests, setup, teardown);
}

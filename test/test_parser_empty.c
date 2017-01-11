#include "test_parser_p.h"

void empty_success(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init("Start", empty()), 1);

  parse_t *result = parse("hello", grammar);
  assert_non_null(result);
  assert_int_equal(result->length, 0);
  assert_int_equal(result->n_children, 0);
}

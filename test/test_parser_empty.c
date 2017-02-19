#include "test_parser_p.h"

void empty_success(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init("Start", empty()), 1);

  parse_result_t *result = parse("hello", grammar);
  assert_non_null(result);

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 0);
  assert_int_equal(suc->n_children, 0);
}

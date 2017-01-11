#include "test_parser_p.h"

void optional_some(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Option"),
    rule_init(
      "Option",
      optional(
        terminal("opt")
      )
    ), 1
  );

  parse_t *result = parse("opt", grammar);
  assert_non_null(result);
  assert_int_equal(result->length, 3);
  assert_int_equal(result->n_children, 1);
}

void optional_none(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Option"),
    rule_init(
      "Option",
      optional(
        terminal("opt")
      )
    ), 1
  );

  parse_t *result = parse("nope", grammar);
  assert_non_null(result);
  assert_int_equal(result->length, 0);
  assert_int_equal(result->n_children, 0);
}

#include "test_parser_p.h"

void not_true(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Not"),
    rule_init(
      "Not",
      sequence(
        not(terminal("hello")),
        terminal("hel")
      )
    ), 1
  );

  parse_result_t *result = parse("help", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  assert_int_equal(result->data.result->length, 3);
}

void not_false(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Not"),
    rule_init(
      "Not",
      sequence(
        not(terminal("hello")),
        terminal("hel")
      )
    ), 1
  );

  parse_result_t *result = parse("hello", grammar);

  assert_non_null(result);
  assert_true(is_error(result));
}

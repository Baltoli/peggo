#include "test_parser.h"

void wrapped_no_end(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      wrapped(
        terminal("["),
        terminal("hello"),
        terminal("]")
      )
    ), 1
  );

  parse_t *result = parse("[hello", grammar);
  assert_null(result);
}

void wrapped_no_start(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      wrapped(
        terminal("["),
        terminal("hello"),
        terminal("]")
      )
    ), 1
  );

  parse_t *result = parse("hello]", grammar);
  assert_null(result);
}

void wrapped_no_inner(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      wrapped(
        terminal("["),
        terminal("hello"),
        terminal("]")
      )
    ), 1
  );

  parse_t *result = parse("[yo]", grammar);
  assert_null(result);
}

void wrapped_success(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      wrapped(
        terminal("["),
        terminal("hello"),
        terminal("]")
      )
    ), 1
  );

  parse_t *result = parse("[hello]", grammar);
  assert_non_null(result);

  assert_int_equal(result->n_children, 3);
  assert_int_equal(result->length, 7);
}

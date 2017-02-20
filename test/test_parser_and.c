#include "test_parser.h"

void and_false(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("And"),
    rule_init(
      "And",
      sequence(
        and(terminal("hello")),
        terminal("h")
      )
    ), 1
  );

  parse_result_t *result = parse("help", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
}

void and_true(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("And"),
    rule_init(
      "And",
      sequence(
        and(terminal("hello")),
        terminal("h")
      )
    ), 1
  );

  parse_result_t *result = parse("hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 1);
  assert_int_equal(suc->n_children, 1);

  assert_int_equal(suc->children[0].length, 1);
  assert_int_equal(suc->children[0].n_children, 0);
}

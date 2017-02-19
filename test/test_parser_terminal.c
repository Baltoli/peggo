#include "test_parser_p.h"

void terminal_success(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("HelloWorld"),
    rule_init("HelloWorld",
      terminal("hello world")
    ), 1
  );

  parse_result_t *result = parse("hello world", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 11);
  assert_int_equal(suc->start, 0);

  assert_int_equal(suc->n_children, 1);
  assert_int_equal(suc->children[0].n_children, 0);
}

void terminal_failure(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("HelloWorld"),
    rule_init("HelloWorld",
      terminal("hello world")
    ), 1
  );

  parse_result_t *result = parse("nope", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
}

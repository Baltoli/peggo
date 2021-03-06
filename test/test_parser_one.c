#include "test_parser.h"

void one_or_more_one(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("One"),
    rule_init(
      "One",
      one_or_more(
        terminal("11")
      )
    ), 1
  );

  parse_result_t *result = parse("11", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 2);
  assert_int_equal(suc->n_children, 1);
}

void one_or_more_many(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("One"),
    rule_init(
      "One",
      one_or_more(
        terminal("11")
      )
    ), 1
  );

  parse_result_t *result = parse("1111111", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 6);
  assert_int_equal(suc->n_children, 3);
}

void one_or_more_failure(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("One"),
    rule_init(
      "One",
      one_or_more(
        terminal("11")
      )
    ), 1
  );

  parse_result_t *result = parse("1", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
}

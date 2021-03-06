#include "test_parser_p.h"

void zero_or_more_zero(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Zero"),
    rule_init(
      "Zero",
      zero_or_more(
        terminal("0")
      )
    ), 1
  );

  parse_result_t *result = parse("asd", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 0);
  assert_int_equal(suc->n_children, 0);
}

void zero_or_more_one(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Zero"),
    rule_init(
      "Zero",
      zero_or_more(
        terminal("0")
      )
    ), 1
  );

  parse_result_t *result = parse("0", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 1);
  assert_int_equal(suc->n_children, 1);
}

void zero_or_more_many(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Zero"),
    rule_init(
      "Zero",
      zero_or_more(
        terminal("0")
      )
    ), 1
  );

  parse_result_t *result = parse("00000", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 5);
  assert_int_equal(suc->n_children, 5);
}

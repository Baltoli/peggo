#include "test_parser_p.h"

void sep_by_zero(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init("Start",
      sep_by(
        terminal("hello"),
        terminal(",")
      )
    ), 1);

  parse_result_t *result = parse("", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 0);
  assert_int_equal(suc->n_children, 0);
  assert_string_equal(suc->symbol, "Start");
}

void sep_by_one(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init("Start",
      sep_by(
        terminal("hello"),
        terminal(",")
      )
    ), 1);

  parse_result_t *result = parse("hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 5);
  assert_int_equal(suc->n_children, 1);
  assert_string_equal(suc->symbol, "Start");

  assert_int_equal(suc->children[0].length, 5);
}

void sep_by_many(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init("Start",
      sep_by(
        terminal("hello"),
        terminal(",")
      )
    ), 1);

  parse_result_t *result = parse("hello,hello,hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 17);
  assert_int_equal(suc->n_children, 5);
  assert_string_equal(suc->symbol, "Start");

  assert_int_equal(suc->children[0].length, 5);
  assert_int_equal(suc->children[1].length, 1);
  assert_int_equal(suc->children[2].length, 5);
  assert_int_equal(suc->children[3].length, 1);
  assert_int_equal(suc->children[4].length, 5);
}

void sep_by_fail(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init("Start",
      sep_by(
        terminal("hello"),
        terminal(",")
      )
    ), 1);

  parse_result_t *result = parse("hello,hello hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 11);
  assert_int_equal(suc->n_children, 3);
  assert_string_equal(suc->symbol, "Start");

  assert_int_equal(suc->children[0].length, 5);
  assert_int_equal(suc->children[1].length, 1);
  assert_int_equal(suc->children[2].length, 5);
}

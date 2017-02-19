#include "test_parser.h"

void whitespace_none(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_result_t *result = parse("none", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  assert_int_equal(result->data.result->length, 0);
}

void whitespace_spaces(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_result_t *result = parse("    ", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 4);
  assert_int_equal(suc->n_children, 4);
}

void whitespace_tabs(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_result_t *result = parse("\t\t", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 2);
  assert_int_equal(suc->n_children, 2);
}

void whitespace_mixed(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_result_t *result = parse(" \t \t ", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 5);
  assert_int_equal(suc->n_children, 5);
}

void whitespace_newlines(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_result_t *result = parse("  \n\t", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 2);
  assert_int_equal(suc->n_children, 2);
}

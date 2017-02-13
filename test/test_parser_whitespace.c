#include "test_parser.h"

void whitespace_none(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_t *result = parse("none", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 0);
}

void whitespace_spaces(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_t *result = parse("    ", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 4);
  assert_int_equal(result->n_children, 4);
}

void whitespace_tabs(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_t *result = parse("\t\t", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 2);
  assert_int_equal(result->n_children, 2);
}

void whitespace_mixed(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_t *result = parse(" \t \t ", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 5);
  assert_int_equal(result->n_children, 5);
}

void whitespace_newlines(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      whitespace()
    ), 1
  );

  parse_t *result = parse("  \n\t", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 2);
  assert_int_equal(result->n_children, 2);
}

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

  parse_t *result = parse("", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 0);
  assert_int_equal(result->n_children, 0);
  assert_string_equal(result->symbol, "Start");
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

  parse_t *result = parse("hello", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 5);
  assert_int_equal(result->n_children, 1);
  assert_string_equal(result->symbol, "Start");

  assert_int_equal(result->children[0].length, 5);
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

  parse_t *result = parse("hello,hello,hello", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 17);
  assert_int_equal(result->n_children, 5);
  assert_string_equal(result->symbol, "Start");

  assert_int_equal(result->children[0].length, 5);
  assert_int_equal(result->children[1].length, 1);
  assert_int_equal(result->children[2].length, 5);
  assert_int_equal(result->children[3].length, 1);
  assert_int_equal(result->children[4].length, 5);
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

  parse_t *result = parse("hello,hello hello", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 11);
  assert_int_equal(result->n_children, 3);
  assert_string_equal(result->symbol, "Start");

  assert_int_equal(result->children[0].length, 5);
  assert_int_equal(result->children[1].length, 1);
  assert_int_equal(result->children[2].length, 5);
}

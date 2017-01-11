#include <stdlib.h>
#include <string.h>

#include "test_parser.h"

static int setup(void **state) {
  return 0;
}

static int teardown(void **state) {
  return 0;
}

void terminal_success(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("HelloWorld"),
    rule_init("HelloWorld",
      terminal("hello world")
    ), 1
  );

  parse_t *result = parse("hello world", grammar);
  assert_int_equal(result->length, 11);
  assert_int_equal(result->start, 0);

  assert_int_equal(result->n_children, 1);
  assert_int_equal(result->children[0].n_children, 0);
}

void terminal_failure(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("HelloWorld"),
    rule_init("HelloWorld",
      terminal("hello world")
    ), 1
  );

  parse_t *result = parse("nope", grammar);
  assert_null(result);
}

void non_terminal_success(void **state) {
  rule_t *rules = malloc(sizeof(*rules) * 2);

  rules[0] = *rule_init("Start",
    non_terminal("NonTerm"));
  rules[1] = *rule_init("NonTerm",
    terminal("hello world"));

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 2);

  parse_t *result = parse("hello world", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 11);
  assert_int_equal(result->n_children, 1);
  assert_string_equal(result->symbol, "Start");

  assert_int_equal(result->children[0].length, 11);
  assert_int_equal(result->children[0].n_children, 1);
  assert_string_equal(result->children[0].symbol, "NonTerm");
}

void non_terminal_failure(void **state) {
  rule_t *rules = malloc(sizeof(*rules) * 2);

  rules[0] = *rule_init("Start",
    non_terminal("NonTerm"));
  rules[1] = *rule_init("NonTerm",
    terminal("hello world"));

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 2);

  parse_t *result = parse("nope", grammar);
  assert_null(result);
}

const struct CMUnitTest parser_tests[] = {
  cmocka_unit_test(terminal_success),
  cmocka_unit_test(terminal_failure),
  cmocka_unit_test(non_terminal_success),
  cmocka_unit_test(non_terminal_failure),
};

int test_parser(void) {
  return cmocka_run_group_tests(parser_tests, setup, teardown);
}

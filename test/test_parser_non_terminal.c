#include "test_parser_p.h"

void non_terminal_success(void **state) {
  rule_t *rules = malloc(sizeof(*rules) * 2);

  rules[0] = *rule_init("Start",
    non_terminal("NonTerm"));
  rules[1] = *rule_init("NonTerm",
    terminal("hello world"));

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 2);

  parse_result_t *result = parse("hello world", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 11);
  assert_int_equal(suc->n_children, 1);
  assert_string_equal(suc->symbol, "Start");

  assert_int_equal(suc->children[0].length, 11);
  assert_int_equal(suc->children[0].n_children, 1);
  assert_string_equal(suc->children[0].symbol, "NonTerm");
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

  parse_result_t *result = parse("nope", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
}

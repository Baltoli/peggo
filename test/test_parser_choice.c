#include "test_parser_p.h"

void choice_first(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Choice"),
    rule_init("Choice",
      choice(
        terminal("hello"),
        terminal("longer")
      )
    ), 1
  );

  parse_result_t *result = parse("hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->n_children, 1);
  assert_int_equal(suc->length, 5);
  
  assert_int_equal(suc->children[0].length, 5);
  assert_int_equal(suc->children[0].n_children, 0);
}

void choice_second(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Choice"),
    rule_init("Choice",
      choice(
        terminal("hello"),
        terminal("longer")
      )
    ), 1
  );

  parse_result_t *result = parse("longer", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->n_children, 1);
  assert_int_equal(suc->length, 6);
  
  assert_int_equal(suc->children[0].length, 6);
  assert_int_equal(suc->children[0].n_children, 0);
}

void choice_longer(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Choice"),
    rule_init("Choice",
      choice(
        terminal("if then else"),
        terminal("if then")
      )
    ), 1
  );

  parse_result_t *result = parse("if then else", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->n_children, 1);
  assert_int_equal(suc->length, 12);
  
  assert_int_equal(suc->children[0].length, 12);
  assert_int_equal(suc->children[0].n_children, 0);
}

void choice_failure(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Choice"),
    rule_init("Choice",
      choice(
        terminal("hello"),
        terminal("longer")
      )
    ), 1
  );

  parse_result_t *result = parse("neither", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
}

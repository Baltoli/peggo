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

  parse_t *result = parse("hello", grammar);
  assert_non_null(result);

  assert_int_equal(result->n_children, 1);
  assert_int_equal(result->length, 5);
  
  assert_int_equal(result->children[0].length, 5);
  assert_int_equal(result->children[0].n_children, 0);
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

  parse_t *result = parse("longer", grammar);
  assert_non_null(result);

  assert_int_equal(result->n_children, 1);
  assert_int_equal(result->length, 6);
  
  assert_int_equal(result->children[0].length, 6);
  assert_int_equal(result->children[0].n_children, 0);
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

  parse_t *result = parse("if then else", grammar);
  assert_non_null(result);

  assert_int_equal(result->n_children, 1);
  assert_int_equal(result->length, 12);
  
  assert_int_equal(result->children[0].length, 12);
  assert_int_equal(result->children[0].n_children, 0);
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

  parse_t *result = parse("neither", grammar);
  assert_null(result);
}

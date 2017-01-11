#include "test_parser_p.h"

void sequence_success(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Seq"),
    rule_init("Seq",
      sequence(
        terminal("hello "),
        terminal("world")
      )
    ), 1
  );

  parse_t *result = parse("hello world", grammar);
  assert_non_null(result);

  assert_int_equal(result->length, 11);
  assert_int_equal(result->n_children, 2);

  assert_int_equal(result->children[0].length, 6);
  assert_int_equal(result->children[0].n_children, 0);
  assert_int_equal(result->children[0].start, 0);

  assert_int_equal(result->children[1].length, 5);
  assert_int_equal(result->children[1].n_children, 0);
  assert_int_equal(result->children[1].start, 6);
}

void sequence_failure(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Seq"),
    rule_init("Seq",
      sequence(
        terminal("hello "),
        terminal("world")
      )
    ), 1
  );

  parse_t *result = parse("not even close", grammar);
  assert_null(result);
}

void sequence_first(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Seq"),
    rule_init("Seq",
      sequence(
        terminal("hello "),
        terminal("world")
      )
    ), 1
  );

  parse_t *result = parse("hello ", grammar);
  assert_null(result);
}

void sequence_second(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Seq"),
    rule_init("Seq",
      sequence(
        terminal("hello "),
        terminal("world")
      )
    ), 1
  );

  parse_t *result = parse("world", grammar);
  assert_null(result);
}

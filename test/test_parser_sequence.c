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

  parse_result_t *result = parse("hello world", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  assert_int_equal(suc->length, 11);
  assert_int_equal(suc->n_children, 2);

  assert_int_equal(suc->children[0].length, 6);
  assert_int_equal(suc->children[0].n_children, 0);
  assert_int_equal(suc->children[0].start, 0);

  assert_int_equal(suc->children[1].length, 5);
  assert_int_equal(suc->children[1].n_children, 0);
  assert_int_equal(suc->children[1].start, 6);
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

  parse_result_t *result = parse("not even close", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
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

  parse_result_t *result = parse("hello ", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
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

  parse_result_t *result = parse("world", grammar);
  assert_non_null(result);
  assert_true(is_error(result));
}

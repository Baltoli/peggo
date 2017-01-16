#include <stdlib.h>
#include <string.h>

#include "test_iterator.h"

static int setup(void **state) {
  return 0;
}

static int teardown(void **state) {
  return 0;
}

void test_iterator_none(void **state) {
  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rule_init(
      "Start",
      terminal("hello")
    ), 1
  );

  parse_t *result = parse("hello", grammar);
  parse_t *begin = parse_non_terminal_begin(result);
  parse_t *end = parse_non_terminal_end(result);

  assert_ptr_equal(begin, end);
}

void test_iterator_one(void **state) {
  rule_t *nested = rule_init(
    "Nested",
    terminal("hello")
  );

  rule_t *start = rule_init(
    "Start",
    non_terminal("Nested")
  );

  rule_t rules[] = { *nested, *start };

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 2
  );

  parse_t *result = parse("hello", grammar);

  parse_t *begin = parse_non_terminal_begin(result);
  parse_t *end = parse_non_terminal_begin(result);
  assert_ptr_not_equal(begin, end);

  parse_t *next = parse_non_terminal_next(result, begin);
  assert_ptr_equal(next, end);
}

void test_iterator_many(void **state) {
  rule_t *nested = rule_init(
    "Start",
    sequence(
      terminal("hello"),
      sequence(
        non_terminal("Space"),
        non_terminal("World")
      )
    ) 
  );

  rule_t *space = rule_init(
    "Space",
    terminal(" ")
  );

  rule_t *world = rule_init(
    "World",
    terminal("world")
  );

  rule_t rules[] = { *nested, *space, *world };

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 4
  );

  parse_t *result = parse("hello world", grammar);
  print_parse(result);

  parse_t *begin = parse_non_terminal_begin(result);
  parse_t *end = parse_non_terminal_begin(result);
  assert_ptr_not_equal(begin, end);

  parse_t *next = parse_non_terminal_next(result, begin);
  assert_ptr_not_equal(next, end);

  next = parse_non_terminal_next(result, next);
  assert_ptr_equal(next, end);
}

const struct CMUnitTest iterator_tests[] = {
  cmocka_unit_test(test_iterator_none),
  cmocka_unit_test(test_iterator_one),
  cmocka_unit_test(test_iterator_many),
};

int test_iterators(void) {
  return cmocka_run_group_tests(iterator_tests, setup, teardown);
}

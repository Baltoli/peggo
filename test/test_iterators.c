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

  parse_result_t *result = parse("hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  parse_t *begin = parse_non_terminal_begin(suc);
  parse_t *end = parse_non_terminal_end(suc);

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

  parse_result_t *result = parse("hello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  parse_t *begin = parse_non_terminal_begin(suc);
  parse_t *end = parse_non_terminal_end(suc);
  assert_ptr_not_equal(begin, end);

  parse_t *next = parse_non_terminal_next(suc, begin);
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

  parse_result_t *result = parse("hello world", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  parse_t *begin = parse_non_terminal_begin(suc);
  parse_t *end = parse_non_terminal_end(suc);
  assert_ptr_not_equal(begin, end);

  parse_t *next = parse_non_terminal_next(suc, begin);
  assert_ptr_not_equal(next, end);

  next = parse_non_terminal_next(suc, next);
  assert_ptr_equal(next, end);
}

void test_iterator_count(void **state) {
  rule_t *nested = rule_init(
    "Nested",
    terminal("hello")
  );

  rule_t *start = rule_init(
    "Start",
    sequence(
      non_terminal("Nested"),
      non_terminal("Nested")
    )
  );

  rule_t rules[] = { *nested, *start };

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 2
  );

  parse_result_t *result = parse("hellohello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  assert_int_equal(parse_non_terminal_count(result->data.result), 2);
}

void test_iterator_collect(void **state) {
  rule_t *nested = rule_init(
    "Nested",
    terminal("hello")
  );

  rule_t *start = rule_init(
    "Start",
    sequence(
      non_terminal("Nested"),
      non_terminal("Nested")
    )
  );

  rule_t rules[] = { *nested, *start };

  grammar_t *grammar = grammar_init(
    non_terminal("Start"),
    rules, 2
  );

  parse_result_t *result = parse("hellohello", grammar);
  assert_non_null(result);
  assert_true(is_success(result));

  parse_t *suc = result->data.result;
  parse_t *children = parse_collect_non_terminals(suc);

  assert_string_equal(children[0].symbol, "Nested");
  assert_string_equal(children[1].symbol, "Nested");

  free(children);
}

const struct CMUnitTest iterator_tests[] = {
  cmocka_unit_test(test_iterator_none),
  cmocka_unit_test(test_iterator_one),
  cmocka_unit_test(test_iterator_many),
  cmocka_unit_test(test_iterator_count),
  cmocka_unit_test(test_iterator_collect),
};

int test_iterators(void) {
  return cmocka_run_group_tests(iterator_tests, setup, teardown);
}

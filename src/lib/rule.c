#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rule.h"
#include "log.h"

rule_t *rule_init(char *sym, expr_t *expr) {
  rule_t *rule = malloc(sizeof(rule_t));
  if(!rule) {
    fatal_error("Could not allocate memory for rule");
  }

  rule->symbol = malloc(strlen(sym) + 1);
  if(!rule->symbol) {
    fatal_error("Could not allocate memory for rule symbol");
  }

  strcpy(rule->symbol, sym);
  rule->production = expr;
  return rule;
}

void rule_free(rule_t *rule) {
  rule_free_unowned(rule);
  free(rule);
}

void rule_free_unowned(rule_t *rule) {
  if(!rule) {
    return;
  }

  expr_free(rule->production);
  free(rule->symbol);
  free(rule);
}

rule_t *rule_collect(size_t count, ...) {
  va_list ap;
  rule_t *rules = malloc(sizeof(rule_t) * count);
  if(!rules) {
    fatal_error("Could not allocate memory for rule collection");
  }

  va_start(ap, count);
  for(size_t i = 0; i < count; i++) {
    rule_t *(*create)(void) = va_arg(ap, rule_t *(*)(void));
    rule_t *newRule = create();
    rules[i] = *newRule;
    free(newRule);
  }
  va_end(ap);

  return rules;
}

void rule_collect_free(size_t count, rule_t *rules) {
  for(size_t i = 0; i < count; i++) {
    rule_free_unowned(&rules[i]);
  }
  free(rules);
}

void print_rule(rule_t *rule) {
  printf("%s ->\n", rule->symbol);
  print_expr_indented(rule->production, 1);
}

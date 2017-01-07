#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rule.h"

rule_t *rule_init(char *sym, expr_t *expr) {
  rule_t *rule = malloc(sizeof(rule_t));
  if(!rule) {
    exit(EXIT_FAILURE);
  }

  rule->symbol = malloc(strlen(sym) + 1);
  if(!rule->symbol) {
    exit(EXIT_FAILURE);
  }

  strcpy(rule->symbol, sym);
  rule->production = expr;
  return rule;
}

void rule_free(rule_t *rule) {
  if(!rule) {
    return;
  }

  expr_free(rule->production);
  free(rule->symbol);
  free(rule);
}

void print_rule(rule_t *rule) {
  printf("%s ->\n", rule->symbol);
  print_expr_indented(rule->production, 1);
}

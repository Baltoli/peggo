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

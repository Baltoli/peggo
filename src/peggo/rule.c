#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rule.h"

peg_rule_t *peg_rule_init(char *sym, peg_expr_t *expr) {
  peg_rule_t *rule = malloc(sizeof(peg_rule_t));
  rule->symbol = malloc(strlen(sym) + 1);
  strcpy(rule->symbol, sym);
  rule->production = expr;
  return rule;
}

void peg_rule_free(peg_rule_t *rule) {
  if(!rule) {
    return;
  }

  peg_free(rule->production);
  free(rule->symbol);
  free(rule);
}

void peg_print_rule(peg_rule_t *rule) {
  printf("%s ->\n", rule->symbol);
  peg_print_expr_indented(rule->production, 1);
}

#ifndef RULE_H
#define RULE_H

#include "expression.h"

typedef struct rule_st {
  char *symbol;
  expr_t *production;
} rule_t;

rule_t *rule_init(char *sym, expr_t *expr);
void rule_free(rule_t *rule);
void print_rule(rule_t *rule);

#endif

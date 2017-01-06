#ifndef RULE_H
#define RULE_H

#include "expression.h"

typedef struct peg_rule_st {
  char *symbol;
  peg_expr_t *production;
} peg_rule_t;

peg_rule_t *peg_rule_init(char *sym, peg_expr_t *expr);
void peg_rule_free(peg_rule_t *rule);
void peg_print_rule(peg_rule_t *rule);

#endif

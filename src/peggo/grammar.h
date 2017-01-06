#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stddef.h>

#include "rule.h"

typedef struct peg_grammar_st {
  peg_expr_t *start;
  peg_rule_t *rules;
  size_t rules_count;
} peg_grammar_t;

peg_grammar_t *peg_grammar_init(peg_expr_t *st, peg_rule_t *rs, size_t rc);
void peg_print_grammar(peg_grammar_t *grammar);

#endif

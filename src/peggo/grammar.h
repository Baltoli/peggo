#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stddef.h>

#include "rule.h"

typedef struct grammar_st {
  expr_t *start;
  rule_t *rules;
  size_t rules_count;
} grammar_t;

grammar_t *grammar_init(expr_t *st, rule_t *rs, size_t rc);
void grammar_free(grammar_t *grammar);
void print_grammar(grammar_t *grammar);
rule_t *grammar_production(grammar_t *grammar, char *symbol);

#endif

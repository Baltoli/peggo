#include <stdio.h>
#include <stdlib.h>

#include "grammar.h"

peg_grammar_t *peg_grammar_init(peg_expr_t *st, peg_rule_t *rs, size_t rc) {
  peg_grammar_t *grammar = malloc(sizeof(*grammar));
  if(!grammar) {
    exit(EXIT_FAILURE);
  }

  grammar->start = st;
  grammar->rules = rs;
  grammar->rules_count = rc;
  return grammar;
}

void peg_print_grammar(peg_grammar_t *grammar) {
  printf("Start: ");
  peg_print_expr(grammar->start);
  printf("\n");
  for(size_t i = 0; i < grammar->rules_count; i++) {
    peg_print_rule(&grammar->rules[i]);
  }
}

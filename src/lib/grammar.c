#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammar.h"

grammar_t *grammar_init(expr_t *st, rule_t *rs, size_t rc) {
  grammar_t *grammar = malloc(sizeof(*grammar));
  if(!grammar) {
    exit(EXIT_FAILURE);
  }

  grammar->start = st;
  grammar->rules = rs;
  grammar->rules_count = rc;
  return grammar;
}

void print_grammar(grammar_t *grammar) {
  printf("Start: ");
  print_expr(grammar->start);
  printf("\n");
  for(size_t i = 0; i < grammar->rules_count; i++) {
    print_rule(&grammar->rules[i]);
  }
}

void grammar_free(grammar_t *grammar) {
  if(!grammar) {
    return;
  }

  expr_free(grammar->start);
  for(size_t i = 0; i < grammar->rules_count; i++) {
    rule_free(&grammar->rules[i]);
  }
}

rule_t *grammar_production(grammar_t *grammar, char *symbol) {
  for(size_t i = 0; i < grammar->rules_count; i++) {
    if(strcmp(symbol, grammar->rules[i].symbol) == 0) {
      return &grammar->rules[i];
    }
  }

  return NULL;
}

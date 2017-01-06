#include <stdlib.h>

#include "grammar.h"

peg_grammar_t *peg_grammar_init(peg_expr_t *st, peg_rule_t *rs, size_t rc) {
  peg_grammar_t *grammar = malloc(sizeof(*grammar));
  grammar->start = st;
  grammar->rules = rs;
  grammar->rules_count = rc;
  return grammar;
}

#ifndef ARITH_GRAMMAR_H
#define ARITH_GRAMMAR_H

#include "peggo.h"

grammar_t *arith_grammar();

rule_t *digit();
rule_t *sign();
rule_t *number();
rule_t *value();

rule_t *add_op();
rule_t *mul_op();

rule_t *product();
rule_t *sum();

rule_t *expr();

#endif

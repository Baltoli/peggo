/** @file */

#ifndef RULE_H
#define RULE_H

#include "expression.h"

/**
 * Represents a single production rule in a PEG grammar.
 *
 * This structure owns the expression it contains.
 */
typedef struct rule_st {
  /**
   * The non-terminal symbol produced by this production rule.
   */
  char *symbol;

  /**
   * The expression specifying how the non-terminal symbol can be produced.
   */
  expr_t *production;
} rule_t;

/**
 * Construct a rule given a symbol and an expression.
 *
 * Copies the symbol \p sym, and takes ownership of \p expr.
 *
 * \param sym The non-terminal symbol
 * \param expr The expression for the production rule
 */
rule_t *rule_init(char *sym, expr_t *expr);

/**
 * Recursively free a rule.
 *
 * This frees the symbol and recursively frees the parse expression.
 */
void rule_free(rule_t *rule);

/**
 * Pretty-print a production rule to `STDOUT`.
 *
 * The format used by this function is very similar to that used by \ref
 * print_expr.
 */
void print_rule(rule_t *rule);

#endif

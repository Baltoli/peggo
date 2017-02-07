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
 * Recursively free a rule when the pointer to the rule itself is not owned.
 *
 * This is the case when the rule is contained within a larger structure
 * deliberately (e.g. as a struct member or an array element), such that freeing
 * the pointer to the rule would be invalid.
 *
 * Should not be used without also freeing the memory containing the rule.
 *
 * \param rule The rule to free
 */
void rule_free_unowned(rule_t *rule);

/**
 * Collect a number of rules into a contiguous array.
 *
 * This is a convenience method that allows for rules to be computed and stored
 * together without manually constructing an array.
 *
 * The pointer returned by this method should be freed by calling \ref
 * rule_collect_free with the correct count.
 *
 * \param count The number of rules to allocate memory for
 * \param ... Variadic argument containing the rules to be constructed. Each
 *            element of the variadic array should be a function declared as
 *            either `rule_t *()` or `rule_t *(void)`.
 */
rule_t *rule_collect(size_t count, ...);

/**
 * Free a continuous array of rules allocated by \ref rule_collect.
 *
 * This should not be called on memory allocated by different functions.
 *
 * \param count The number of rules to be freed
 * \param rules The array containing rules to be freed
 */
void rule_collect_free(size_t count, rule_t *rules);

/**
 * Pretty-print a production rule to `STDOUT`.
 *
 * The format used by this function is very similar to that used by \ref
 * print_expr.
 */
void print_rule(rule_t *rule);

#endif

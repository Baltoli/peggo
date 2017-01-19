/** @file */

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stddef.h>

#include "rule.h"

/**
 * Represents a full PEG grammar with production rules and starting symbol.
 *
 * This structure owns its starting expression and all its rules once
 * constructed.
 */
typedef struct grammar_st {
  /**
   * The starting expression of the grammar.
   */
  expr_t *start;

  /**
   * The production rules for the grammar.
   */
  rule_t *rules;

  /**
   * The number of production rules in the grammar.
   */
  size_t rules_count;
} grammar_t;

/**
 * Construct a \ref grammar_t.
 *
 * \p rs must point to an allocated region of memory at least \p rc elements in
 * length, where each element is a valid instance of \ref rule_t.
 *
 * This constructor takes ownership of \p st and exactly \p rc elements of \p rs
 *
 * \param st The starting expression of the grammar
 * \param rs The production rules of the grammar
 * \param rc The number of production rules
 */
grammar_t *grammar_init(expr_t *st, rule_t *rs, size_t rc);

/**
 * Recursively free a \ref grammar_t.
 *
 * Calling this function will free the grammar along with its starting
 * expression and all its production rules.
 *
 * \param grammar The grammar to be freed
 */
void grammar_free(grammar_t *grammar);

/**
 * Pretty print a grammar to `STDOUT`.
 *
 * Prints the starting symbol of the grammar, and each production rule. The
 * printing format is similar to that used by \ref print_expr.
 */
void print_grammar(grammar_t *grammar);

/**
 * Look up the production rule for a non-terminal symbol in a grammar.
 *
 * Performs a search of the rules associated with \p grammar. If no match is
 * found, `NULL` is returned. If a rule is returned, \p grammar retains
 * ownership of it.
 *
 * \param grammar The grammar to use for the lookup
 * \param symbol The symbol to search for
 */
rule_t *grammar_production(grammar_t *grammar, char *symbol);

#endif

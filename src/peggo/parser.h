/** @file */

#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include "parse_tree.h"

/**
 * Parse a string using a PEG grammar.
 *
 * This function is **not** thread safe, as \p grammar is stored in a global
 * variable for implementation purposes. If multiple threads need to call the
 * parser, they should do so in mutual exclusion.
 *
 * Does not take ownership of \p source or \p grammar. They may both be used
 * freely after a call to \ref parse.
 *
 * \param source A source text to be parsed
 * \param grammar The grammar with which to parse the source
 */
parse_t *parse(char *source, grammar_t *grammar);

#endif

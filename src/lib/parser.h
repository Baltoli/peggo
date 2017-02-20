/** @file */

#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include "parse_tree.h"

/**
 * Tag type for parse results.
 *
 * Describes if the result of a parse is an error or holds some data.
 */
enum parse_result_kind {
  ERROR = 0,
  RESULT
};

/**
 * Holds information about a parsing error.
 */
typedef struct parse_error_st {
  /**
   * A message describing the error that occured.
   */
  char *message;
} parse_error_t;

/**
 * Tagged union type that can hold a parsing error or a valid result.
 */
typedef struct parse_result_st {
  /**
   * The parsing data (error or valid result).
   */
  union {
    parse_t *result;
    parse_error_t *error;
  } data;

  /**
   * Tag specifying which kind of data is stored in the union.
   */
  enum parse_result_kind data_kind;
} parse_result_t;

/**
 * Initialise a parse error structure with a message.
 *
 * The string passed is copied into the error structure. Errors allocated using
 * this method should only be freed using \ref parse_error_free.
 *
 * \param message String describing the error
 */
parse_error_t *parse_error_init(char *message);

/**
 * Free a parse error structure.
 *
 * This should only be used on errors allocated with \ref parse_error_init.
 *
 * \param err The error to be freed. May be `NULL`.
 */
void parse_error_free(parse_error_t *err);

/**
 * Wrap a \ref parse_t result into a \ref parse_result_t.
 *
 * The \ref parse_t passed is owned by the returned structure. The pointer
 * returned from this function should only be freed using \ref
 * parse_result_free.
 *
 * \param result The successful result to be encapsulated.
 */
parse_result_t *make_result(parse_t *result);

/**
 * Wrap a \ref parse_error_t error into a \ref parse_result_t.
 *
 * The \ref parse_error_t passed is owned by the returned structure. The pointer
 * returned from this function should only be freed using \ref
 * parse_result_free.
 *
 * \param error The error to be encapsulated.
 */
parse_result_t *make_error(parse_error_t *error);

/**
 * Free a \ref parse_result_t.
 *
 * This function frees the data stored in the result (whether it is a success or
 * an error).
 *
 * \param result The result to be freed. May be `NULL`.
 */
void parse_result_free(parse_result_t *result);

/**
 * Returns true if a result is an error value.
 *
 * \param result The result to check
 */
bool is_error(parse_result_t *result);

/**
 * Returns true if a result is a success value.
 *
 * \param result The result to check
 */
bool is_success(parse_result_t *result);

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
 * If a parse is successful, the object returned will be a \ref SUCCESS variant
 * with a \ref parse_t member in its union. Similarly, if the parse fails then
 * it will be an \ref ERROR variant.
 *
 * \param source A source text to be parsed
 * \param grammar The grammar with which to parse the source
 */
parse_result_t *parse(char *source, grammar_t *grammar);

#endif

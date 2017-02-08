/** @file */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "expression.h"

/**
 * Parse a sequence of expressions separated by another expression.
 *
 * This parsing expression will match zero or more instances of \p expr, provided
 * that between each instance of \p expr, there is an instance of \p sep.
 *
 * \param expr The expression in sequence
 * \param sep The separator
 */
expr_t *sep_by(expr_t *expr, expr_t *sep);

#endif

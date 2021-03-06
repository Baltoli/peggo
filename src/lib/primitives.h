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

/**
 * Parse whitespace that does not extend over a line boundary.
 *
 * This expression matches zero or more spaces or tabs, but will not match line
 * separators like '\n'.
 */
expr_t *whitespace();

/**
 * Parse an expression that is wrapped inside a pair of outer expressions.
 *
 * An example of this could be an expression wrapped in parentheses. This
 * expression will match exactly one left, one inner, then one right.
 *
 * \param left The left-hand expression
 * \param inner The inner expression
 * \param right The right-hand expression
 */
expr_t *wrapped(expr_t *left, expr_t *inner, expr_t *right);

#endif

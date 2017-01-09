/** @file */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdbool.h>

/**
 * Represents the type of a parsing expression.
 *
 * Each of these values represents a type of syntactic construct in the language
 * of PEG expressions.
 */
typedef enum expr_node_en {
  Node_Invalid = 0,
  Node_Empty,
  Node_Terminal,
  Node_Non_Terminal,
  Node_Sequence,
  Node_Choice,
  Node_Zero_Or_More,
  Node_One_Or_More,
  Node_Optional,
  Node_And,
  Node_Not
} expr_node_t;

/**
 * Represents a single node in a tree-structured PEG parsing expression.
 *
 * This structure recursively describes a PEG parsing expression. All nodes of
 * this type take ownership of their child nodes when they are constructed.
 */
typedef struct expr_st {
  /**
   * The type of the node (i.e. which syntactic construct it represents)
   */
  enum expr_node_en type;

  /**
   * Optional string data to be associated with this node.
   *
   * This field should only be used for terminal and non-terminal nodes in the
   * grammar. For terminals, it contains the literal to be matched. For
   * non-terminals, it contains the symbol name to be produced.
   */
  char *data;

  /**
   * Left child node.
   *
   * For node types with two children (sequence or choice), this holds the first
   * of the two child nodes. For types with only a single child, this holds that
   * child.
   */
  struct expr_st *left;

  /**
   * Right child node.
   *
   * For node types with two children (sequence or choice), this holds the first
   * of the two child nodes. For types with only a single child, this field is
   * unused.
   */
  struct expr_st *right;
} expr_t;

/**
 * Recursively frees an \ref expr_t that has been allocated by one of the typed
 * constructors.
 *
 * All child nodes will be recursively freed by a call to this function. If the
 * argument is `NULL`, this function does nothing.
 *
 * \param node The expression to be freed
 */
void expr_free(expr_t *node);

/**
 * Construct an expression node representing the empty expression.
 */
expr_t *empty(void);

/**
 * Construct an expression node representing a terminal symbol.
 *
 * The argument string passed is copied, and so the constructed node *does not*
 * take ownership of the argument.
 *
 * \param t The literal string to be matched
 */
expr_t *terminal(const char *t);

/**
 * Construct an expression node representing a non-terminal symbol.
 *
 * The argument string passed is copied, and so the constructed node *does not*
 * take ownership of the argument.
 *
 * \param nt The non-terminal symbol name to be produced
 */
expr_t *non_terminal(const char *nt);

/**
 * Construct an expression node representing a sequence of two expressions.
 *
 * The constructed node takes ownership of the two child nodes passed as
 * parameters.
 *
 * \param left The first expression to be matched
 * \param right The second expression to be matched
 */
expr_t *sequence(expr_t *left, expr_t *right);

/**
 * Construct an expression node representing a sequence of a child expression
 * that may be zero-length.
 *
 * The constructed node takes ownership of the child node passed as a parameter.
 *
 * \param expr The child expression to be repeated
 */
expr_t *zero_or_more(expr_t *expr);

/**
 * Construct an expression node representing a sequence of a child expression
 * that cannot be zero-length.
 *
 * The constructed node takes ownership of the child node passed as a parameter.
 *
 * \param expr The child expression to be repeated
 */
expr_t *one_or_more(expr_t *expr);

/**
 * Construct an expression node representing an ordered choice between two
 * expressions.
 *
 * The constructed node takes ownership of the two child nodes passed as
 * parameters.
 *
 * \param left The first expression to be matched if possible
 * \param second The second expression to be matched
 */
expr_t *choice(expr_t *left, expr_t *right);

/**
 * Construct an expression node representing an optional match of a child
 * expression.
 *
 * The constructed node takes ownership of the child node passed as a parameter.
 *
 * \param expr The expression to be optionally matched
 */
expr_t *optional(expr_t *expr);

/**
 * Construct an expression node representing a positive syntactic predicate.
 *
 * The constructed node takes ownership of the child node passed as a parameter.
 *
 * \param expr The expression to be checked
 */
expr_t *and(expr_t *expr);

/**
 * Construct an expression node representing a negative syntactic predicate.
 *
 * The constructed node takes ownership of the child node passed as a parameter.
 *
 * \param expr The expression to be checked
 */
expr_t *not(expr_t *expr);

/**
 * Check whether an expression node has the given type.
 *
 * \param node The expression to be tested
 * \param type The type to check for
 */
bool isa(expr_t *node, expr_node_t type);

/**
 * Maps an expression node to a string representing its type.
 *
 * \param node The expression to map to a name
 */
const char *expr_name(expr_t *node);

/**
 * Pretty-prints an expression to `STDOUT`.
 *
 * Subexpressions are indented appropriately, and terminal / non-terminal nodes
 * have their symbols printed as well.
 */
void print_expr(expr_t *node);

/**
 * Pretty-prints an expression to `STDOUT` at a given indentation level.
 *
 * Subexpressions are indented appropriately, and terminal / non-terminal nodes
 * have their symbols printed as well.
 *
 * The format used for indentation is determined by \ref print_indents
 */
void print_expr_indented(expr_t *node, int indent);

#endif

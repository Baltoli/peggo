#ifndef AST_H
#define AST_H

#include "peggo.h"

typedef enum op_type_en {
  INVALID = 0,
  ADD, SUB, MUL, DIV
} op_type;

typedef enum node_type_en {
  LEAF, BRANCH
} node_type;

typedef struct ast_st {
  op_type op;
  node_type type;
  struct ast_st *left;
  struct ast_st *right;
  long long value;
} ast_t;

ast_t *literal(long long v);
ast_t *op(ast_t *left, op_type op, ast_t *right);
void ast_free(ast_t *t);

void print_ast(ast_t *a);
void print_ast_indented(ast_t *a, int indents);

op_type extract_op(char *src, parse_t *result);
ast_t *extract(char *src, parse_t *result);
ast_t *extract_number(char *src, parse_t *result);
ast_t *extract_value(char *src, parse_t *result);
ast_t *extract_seq(char *src, parse_t *result, size_t off);
ast_t *extract_expr(char *src, parse_t *result);

long long eval(ast_t *a);

#endif

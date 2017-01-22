#ifndef AST_H
#define AST_H

typedef enum op_type_en {
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

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "log.h"

ast_t *literal(long long v) {
  ast_t *node = malloc(sizeof(*node));
  if(!node) {
    fatal_error("Could not allocate memory for literal AST node");
  }

  node->type = LEAF;
  node->value = v;

  return node;
}

ast_t *op(ast_t *left, op_type ty, ast_t *right) {
  ast_t *node = malloc(sizeof(*node));
  if(!node) {
    fatal_error("Could not allocate memory for binary op AST node");
  }

  node->type = BRANCH;
  node->op = ty;
  node->left = left;
  node->right = right;

  return node;
}

void ast_free(ast_t *node) {
  if(!node) {
    return;
  }

  if(node->type == BRANCH) {
    ast_free(node->left);
    ast_free(node->right);
  }

  free(node);
}

op_type extract_op(char *src, parse_t *result) {
  if(result->terminal) {
    return INVALID;
  }

  char *sym = result->symbol;

  switch(*(src+result->start)) {
    case '+':
      return ADD;
    case '-':
      return SUB;
    case '*':
      return MUL;
    case '/':
      return DIV;
  }

  return INVALID;
}

ast_t *extract(char *src, parse_t *result) {
  if(result->terminal) {
    return NULL;
  }

  char *sym = result->symbol;

  if(strcmp(sym, "Number") == 0) {
    return extract_number(src, result);
  } else if(strcmp(sym, "Value") == 0) {
    return extract_value(src, result);
  } else if(strcmp(sym, "Product") == 0) {
    return extract_seq(src, result, 0);
  } else if(strcmp(sym, "Sum") == 0) {
    return extract_seq(src, result, 0);
  } else if(strcmp(sym, "Expr") == 0) {
    return extract_expr(src, result);
  }

  return NULL;
}

ast_t *extract_number(char *src, parse_t *result) {
  char *begin = src + result->start;
  char *copy = malloc(result->length + 1);

  strncpy(copy, begin, result->length + 1);
  long long v = strtoll(copy, NULL, 10);
  free(copy);

  return literal(v);
}

ast_t *extract_value(char *src, parse_t *result) {
  size_t ntc = parse_non_terminal_count(result);
  if(ntc != 1) {
    return NULL;
  }

  return extract(src, parse_non_terminal_begin(result));
}

ast_t *extract_seq(char *src, parse_t *result, size_t off) {
  size_t ntc = parse_non_terminal_count(result);
  if(ntc == 1) {
    return extract(src, parse_non_terminal_begin(result));
  }

  parse_t *left = parse_non_terminal_begin(result);
  for(size_t i = 0; i < off; i++) {
    left = parse_non_terminal_next(result, left);
  }

  parse_t *op_ty = parse_non_terminal_next(result, left);
  parse_t *rest = parse_non_terminal_next(result, op_ty);

  if(parse_non_terminal_next(result, rest) == parse_non_terminal_end(result)) {
    return op(extract(src, left), extract_op(src, op_ty), extract(src, rest));
  }

  return op(extract(src, left), extract_op(src, op_ty), extract_seq(src, result, off+2));
}

ast_t *extract_expr(char *src, parse_t *result) {
  return extract(src, parse_non_terminal_begin(result));
}

void print_ast(ast_t *a) {
  print_ast_indented(a, 0);
  printf("\n");
}

void print_ast_indented(ast_t *a, int indents) {
  if(a->type == LEAF) {
    printf("%lld", a->value);
  } else if(a->type == BRANCH) {
    printf("(");
    switch(a->op) {
      case ADD:
        printf("+");
        break;
      case SUB:
        printf("-");
        break;
      case MUL:
        printf("*");
        break;
      case DIV:
        printf("/");
        break;
      default:
        printf("Invalid\n");
        break;
    }
    printf(" ");
    print_ast_indented(a->left, 0);
    printf(" ");
    print_ast_indented(a->right, 0);
    printf(")");
  }
}

long long eval(ast_t *a) {
  if(a->type == LEAF) {
    return a->value;
  }

  switch(a->op) {
    case ADD:
      return eval(a->left) + eval(a->right);
      break;
    case SUB:
      return eval(a->left) - eval(a->right);
      break;
    case MUL:
      return eval(a->left) * eval(a->right);
      break;
    case DIV:
      return eval(a->left) / eval(a->right);
      break;
    default:
      fatal_error("Invalid operation when evaluating AST");
  }
}

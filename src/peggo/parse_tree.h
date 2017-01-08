#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <stddef.h>

typedef struct parse_st {
  char *symbol;
  size_t start;
  size_t length;
  struct parse_st *children;
  size_t n_children;
} parse_t;

parse_t *parse_init(char *s, size_t st, size_t len);
void parse_free(parse_t *tree);
void parse_add_child(parse_t *tree, parse_t *child);
void print_parse_indented(parse_t *tree, int indent);
void print_parse(parse_t *tree);
size_t parse_total_length(parse_t *tree);

#endif

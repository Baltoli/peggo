#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <stddef.h>

typedef struct peg_parse_st {
  char *symbol;
  size_t start;
  size_t length;
  struct peg_parse_st *children;
  size_t n_children;
} peg_parse_t;

peg_parse_t *peg_parse_init(char *s, size_t st, size_t len);
void peg_parse_free(peg_parse_t *tree);
void peg_parse_add_child(peg_parse_t *tree, peg_parse_t *child);

#endif

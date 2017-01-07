#include <stdlib.h>
#include <string.h>

#include "parse_tree.h"

peg_parse_t *peg_parse_init(char *s, size_t st, size_t len) {
  peg_parse_t *tree = malloc(sizeof(peg_parse_t));
  if(!tree) {
    exit(EXIT_FAILURE);
  }

  tree->symbol = malloc(strlen(s) + 1); 
  if(!tree->symbol) {
    exit(EXIT_FAILURE);
  }
  strcpy(tree->symbol, s);

  tree->start = st;
  tree->length = len;

  tree->children = NULL;
  tree->n_children = 0;

  return tree;
}

void peg_parse_free(peg_parse_t *tree) {
  if(!tree) {
    return;
  }

  free(tree->symbol);  

  for(size_t i = 0; i < tree->n_children; i++) {
    peg_parse_free(&tree->children[i]);
  }
}

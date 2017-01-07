#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
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

void peg_parse_add_child(peg_parse_t *tree, peg_parse_t *child) {
  if(!tree || !child) {
    return;
  }

  if(tree->children) {
    tree->children = realloc(tree->children, sizeof(peg_parse_t) * (tree->n_children + 1));
  } else {
    tree->children = malloc(sizeof(peg_parse_t));
  }

  if(!tree->children) {
    exit(EXIT_FAILURE);
  }

  tree->children[tree->n_children] = *child;
  tree->n_children++;
}

void peg_print_parse_indented(peg_parse_t *tree, int indent) {
  print_indents(indent);

  printf("%s [%zu, %zu)\n", tree->symbol, tree->start, tree->start + tree->length);
  for(size_t i = 0; i < tree->n_children; i++) {
    peg_print_parse_indented(&tree->children[i], indent + 1);
  }
}

void peg_print_parse(peg_parse_t *tree) {
  peg_print_parse_indented(tree, 0);
}

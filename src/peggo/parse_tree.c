#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parse_tree.h"

parse_t *parse_init(char *s, size_t st, size_t len) {
  parse_t *tree = malloc(sizeof(parse_t));
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

void parse_free(parse_t *tree) {
  if(!tree) {
    return;
  }

  free(tree->symbol);  

  for(size_t i = 0; i < tree->n_children; i++) {
    parse_free(&tree->children[i]);
  }
}

void parse_add_child(parse_t *tree, parse_t *child) {
  if(!tree || !child) {
    return;
  }

  if(tree->children) {
    tree->children = realloc(tree->children, sizeof(parse_t) * (tree->n_children + 1));
  } else {
    tree->children = malloc(sizeof(parse_t));
  }

  if(!tree->children) {
    exit(EXIT_FAILURE);
  }

  tree->children[tree->n_children] = *child;
  tree->n_children++;
}

void print_parse_indented(parse_t *tree, int indent) {
  print_indents(indent);

  printf("%s [%zu, %zu)\n", tree->symbol, tree->start, tree->start + tree->length);
  for(size_t i = 0; i < tree->n_children; i++) {
    print_parse_indented(&tree->children[i], indent + 1);
  }
}

void print_parse(parse_t *tree) {
  print_parse_indented(tree, 0);
}

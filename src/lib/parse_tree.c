#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parse_tree.h"
#include "log.h"

parse_t *parse_init(char *s, size_t st, size_t len) {
  parse_t *tree = malloc(sizeof(parse_t));
  if(!tree) {
    fatal_error("Could not allocate memory for parse tree");
  }

  tree->symbol = malloc(strlen(s) + 1); 
  if(!tree->symbol) {
    fatal_error("Could not allocate memory for parse tree symbol");
  }
  strcpy(tree->symbol, s);

  tree->start = st;
  tree->length = len;

  tree->children = NULL;
  tree->n_children = 0;

  tree->terminal = false;

  return tree;
}

void parse_free_child(parse_t *tree) {
  if(!tree) {
    return;
  }

  free(tree->symbol);  

  for(size_t i = 0; i < tree->n_children; i++) {
    parse_free_child(&tree->children[i]);
  }
  free(tree->children);
}

void parse_free(parse_t *tree) {
  parse_free_child(tree);
  free(tree);
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
    fatal_error("Parse tree child pointer is not initialised");
  }

  tree->children[tree->n_children] = *child;
  tree->n_children++;
}

void print_parse_indented(parse_t *tree, int indent) {
  if(!tree) {
    printf("[NO PARSE]\n");
    return;
  }

  print_indents(indent);

  printf("%s [%zu, %zu) %s\n", tree->symbol, tree->start, tree->start + tree->length, tree->terminal?"terminal":"");
  for(size_t i = 0; i < tree->n_children; i++) {
    print_parse_indented(&tree->children[i], indent + 1);
  }
}

void print_parse(parse_t *tree) {
  print_parse_indented(tree, 0);
}

size_t parse_total_length(parse_t *tree) {
  size_t len = 0;
  for(size_t i = 0; i < tree->n_children; i++) {
    len += tree->children[i].length;
  }
  return len;
}

size_t parse_non_terminal_count(parse_t *tree) {
  size_t count = 0;
  parse_t *child = parse_non_terminal_begin(tree);
  
  while(child != parse_non_terminal_end(tree)) {
    count++;
    child = parse_non_terminal_next(tree, child);
  }

  return count;
}

parse_t *parse_collect_non_terminals(parse_t *tree) {
  size_t count = parse_non_terminal_count(tree);
  if(count == 0) {
    return NULL;
  }

  parse_t *buf = malloc(sizeof(*buf) * count);
  if(!buf) {
    fatal_error("Could not allocate memory for non-terminal collection buffer");
  }

  parse_t *child = parse_non_terminal_begin(tree);
  size_t i = 0;
  while(child != parse_non_terminal_end(tree)) {
    buf[i++] = *child;
    child = parse_non_terminal_next(tree, child);
  }

  return buf;
}

parse_t *parse_non_terminal_begin(parse_t *tree) {
  return parse_non_terminal_next(tree, tree->children - 1);
}

parse_t *parse_non_terminal_end(parse_t *tree) {
  return tree->children + tree->n_children;
}

parse_t *parse_non_terminal_next(parse_t *tree, parse_t *child) {
  parse_t *result = child + 1;
  parse_t *end = parse_non_terminal_end(tree);

  while(result != end && result->terminal) {
    result++;
  }

  return result;
}

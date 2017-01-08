#include <stdlib.h>
#include <string.h>

#include "parser.h"

parse_t *parse(char *source, grammar_t *grammar) {
  return NULL;
}

parse_t *parse_empty(char *source, size_t start, parse_t *parent) {
  parse_t *node = parse_init("__empty", start, 0);
  parse_add_child(parent, node);
  return node;
}

parse_t *parse_terminal(char *source, char *symbol, size_t start, parse_t *parent) {
  size_t len = strlen(symbol);

  for(size_t i = 0; i < len; i++) {
    if(source[i + start] != symbol[i]) {
      return NULL;
    }
  }

  char *annotated = malloc(len + 2);
  if(!annotated) {
    exit(EXIT_FAILURE);
  }

  strcpy(annotated, "'");
  strcpy(annotated + 1, symbol);
  strcpy(annotated + len + 1, "'");

  parse_t *ret = parse_init(annotated, start, len);
  parse_add_child(parent, ret);

  free(annotated);
  return ret;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static grammar_t *grammar;

parse_t *parse(char *source, grammar_t *gram) {
  grammar = gram;

  parse_t *parent = parse_dispatch(source, gram->start, 0, NULL);
  if(!parent) {
    return NULL;
  }

  parent->length = parse_total_length(parent);
  return parent;
}

parse_t *parse_dispatch(char *source, expr_t *rule, size_t start, parse_t *parent) {
  if(!rule) {
    return NULL;
  }

  switch(rule->type) {
    case Node_Empty:
      return parse_empty(source, start, parent);
    case Node_Terminal:
      return parse_terminal(source, rule->data, start, parent);
    case Node_Non_Terminal:
      return parse_non_terminal(source, rule->data, start, parent);
  }

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

parse_t *parse_non_terminal(char *source, char *symbol, size_t start, parse_t *parent) {
  rule_t *rule = grammar_production(grammar, symbol);
  if(!rule) {
    printf("Invalid grammar - no rule for non-terminal %s\n", symbol);
    exit(EXIT_FAILURE);
  }

  parse_t *this = parse_init(symbol, start, 0);
  parse_t *result = parse_dispatch(source, rule->production, start, this);
  if(!result) {
    return NULL;
  }

  this->length = parse_total_length(this);
  
  parse_add_child(parent, this);
  return this;
}

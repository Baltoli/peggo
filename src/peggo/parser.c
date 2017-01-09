#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "parser_p.h"

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
    case Node_Sequence:
      return parse_sequence(source, rule->left, rule->right, start, parent);
    case Node_Choice:
      return parse_choice(source, rule->left, rule->right, start, parent);
    case Node_Zero_Or_More:
      return parse_zero_or_more(source, rule->left, start, parent);
    case Node_One_Or_More:
      return parse_one_or_more(source, rule->left, start, parent);
    case Node_Optional:
      return parse_optional(source, rule->left, start, parent);
    case Node_And:
      return parse_and(source, rule->left, start);
    case Node_Not:
      return parse_not(source, rule->left, start);
    default:
      printf("Invalid node in grammar - fatal error\n");
      exit(EXIT_FAILURE);
  }

  return NULL;
}

parse_t *parse_empty(char *source, size_t start, parse_t *parent) {
  return parse_init("__empty", start, 0);
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

parse_t *parse_sequence(char *source, expr_t *left, expr_t *right, size_t start, parse_t *parent) {
  if(!left || !right) {
    return NULL;
  }

  parse_t *left_result = parse_dispatch(source, left, start, parent);
  if(!left_result) {
    return NULL;
  }

  parse_t *right_result = parse_dispatch(source, right, start + left_result->length, parent);
  if(!right_result) {
    parse_free(left_result);
    return NULL;
  }

  left_result->length += right_result->length;
  return left_result;
}

parse_t *parse_choice(char *source, expr_t *left, expr_t *right, size_t start, parse_t *parent) {
  if(!left || !right) {
    return NULL;
  }

  parse_t *left_result = parse_dispatch(source, left, start, parent);
  if(left_result) {
    return left_result;
  }

  parse_t *right_result = parse_dispatch(source, right, start, parent);
  return right_result;
}

parse_t *parse_zero_or_more(char *source, expr_t *expr, size_t start, parse_t *parent) {
  if(!expr) {
    return NULL;
  }

  size_t offset = start;
  parse_t *result = NULL;

  while((result = parse_dispatch(source, expr, offset, parent))) {
    offset += result->length;
  }

  parse_t *ret = result ? result : parse_init("__plus_end", offset, 0);
  ret->length = offset - start;
  return ret;
}

parse_t *parse_one_or_more(char *source, expr_t *expr, size_t start, parse_t *parent) {
  if(!expr) {
    return NULL;
  }

  size_t offset = start;
  parse_t *result, *prev = NULL;

  while((result = parse_dispatch(source, expr, offset, parent))) {
    prev = result;
    offset += result->length;
  }

  if(prev) {
    prev->length = offset - start;
  }

  return prev;
}

parse_t *parse_optional(char *source, expr_t *expr, size_t start, parse_t *parent) {
  if(!expr) {
    return NULL;
  }

  parse_t *result = parse_dispatch(source, expr, start, parent);
  return result ? result : parse_init("__optional", start, 0);
}

parse_t *parse_and(char *source, expr_t *expr, size_t start) {
  if(!expr) {
    return NULL;
  }

  parse_t *result = parse_dispatch(source, expr, start, NULL);

  if(result) {
    return parse_init("__and", start, 0);
  }

  return NULL;
}

parse_t *parse_not(char *source, expr_t *expr, size_t start) {
  if(!expr) {
    return NULL;
  }

  parse_t *result = parse_dispatch(source, expr, start, NULL);
  if(result) {
    return NULL;
  }

  return parse_init("__not", start, 0);
}

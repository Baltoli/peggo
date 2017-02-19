#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "parser_p.h"
#include "log.h"

static _Thread_local grammar_t *grammar;

parse_error_t *parse_error_init(char *message) {
  parse_error_t *err = malloc(sizeof(*err));
  if(!err) {
    fatal_error("Could not allocate memory for parse error");
  }
  
  err->message = malloc(strlen(message) + 1);
  if(!err->message) {
    fatal_error("Could not allocate memory for parse error message");
  }
  strcpy(err->message, message);
  
  return err;
}

void parse_error_free(parse_error_t *err) {
  if(!err) {
    return;
  }

  free(err->message);
  free(err);
}

parse_result_t *parse_result_init() {
  parse_result_t *res = malloc(sizeof(*res));
  if(!res) {
    fatal_error("Could not allocate memory for parse result");
  }

  return res;
}

parse_result_t *make_result(parse_t *result) {
  assert(result && "Can't make_result from NULL");

  parse_result_t *res = parse_result_init();
  res->data.result = result;
  res->data_kind = RESULT;
  return res;
}

parse_result_t *make_error(parse_error_t *error) {
  assert(error && "Can't make_error from NULL");

  parse_result_t *res = parse_result_init();
  res->data.error = error;
  res->data_kind = ERROR;
  return res;
}

void parse_result_free(parse_result_t *result) {
  if(!result) {
    return;
  }

  switch(result->data_kind) {
    case RESULT:
      parse_free(result->data.result);
      break;
    case ERROR:
      parse_error_free(result->data.error);
      break;
  }

  free(result);
}

bool is_error(parse_result_t *result) {
  return result->data_kind == ERROR;
}

bool is_success(parse_result_t *result) {
  return result->data_kind == RESULT;
}

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
      fatal_error("Invalid node in grammar");
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

  char *annotated = malloc(len + 3);
  if(!annotated) {
    fatal_error("Could not allocate memory for annotated terminal symbol");
  }

  strcpy(annotated, "'");
  strcpy(annotated + 1, symbol);
  strcpy(annotated + len + 1, "'");

  parse_t *ret = parse_init(annotated, start, len);
  ret->terminal = true;
  parse_add_child(parent, ret);

  free(annotated);
  return ret;
}

parse_t *parse_non_terminal(char *source, char *symbol, size_t start, parse_t *parent) {
  rule_t *rule = grammar_production(grammar, symbol);
  if(!rule) {
    fatal_error("Invalid grammar - no rule for a non-terminal");
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

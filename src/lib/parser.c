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

parse_result_t *parse(char *source, grammar_t *gram) {
  grammar = gram;

  parse_result_t *parent = parse_dispatch(source, gram->start, 0, NULL);

  if(is_success(parent)) {
    parent->data.result->length = parse_total_length(parent->data.result);
  }

  return parent;
}

parse_result_t *parse_dispatch(char *source, expr_t *rule, size_t start, parse_result_t *parent) {
  if(!rule) {
    return make_error(parse_error_init("No parsing rule specified!"));
  }

  if(is_error(parent)) {
    return parent;
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
}

parse_result_t *parse_empty(char *source, size_t start, parse_result_t *parent) {
  return make_result(parse_init("__empty", start, 0));
}

parse_result_t *parse_terminal(char *source, char *symbol, size_t start, parse_result_t *parent) {
  size_t len = strlen(symbol);

  for(size_t i = 0; i < len; i++) {
    if(source[i + start] != symbol[i]) {
      return make_error(parse_error_init("Failed to parse terminal"));
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
  parse_add_child(parent->data.result, ret);

  free(annotated);
  return make_result(ret);
}

parse_result_t *parse_non_terminal(char *source, char *symbol, size_t start, parse_result_t *parent) {
  rule_t *rule = grammar_production(grammar, symbol);
  if(!rule) {
    fatal_error("Invalid grammar - no rule for a non-terminal");
  }

  parse_t *this = parse_init(symbol, start, 0);
  parse_result_t *result = parse_dispatch(source, rule->production, start, make_result(this));
  if(is_error(result)) {
    return result;
  }

  this->length = parse_total_length(this);
  
  parse_add_child(parent->data.result, this);
  return make_result(this);
}

parse_result_t *parse_sequence(char *source, expr_t *left, expr_t *right, size_t start, parse_result_t *parent) {
  if(!left || !right) {
    fatal_error("Can't parse sequence with NULL operands");
  }

  parse_result_t *left_result = parse_dispatch(source, left, start, parent);
  if(is_error(left_result)) {
    return left_result;
  }

  parse_result_t *right_result = parse_dispatch(source, right, start + left_result->data.result->length, parent);
  if(is_error(right_result)) {
    parse_result_free(left_result);
    return right_result;
  }

  left_result->data.result->length += right_result->data.result->length;
  return left_result;
}

parse_result_t *parse_choice(char *source, expr_t *left, expr_t *right, size_t start, parse_result_t *parent) {
  if(!left || !right) {
    fatal_error("Can't parse choice with NULL operands");
  }

  parse_result_t *left_result = parse_dispatch(source, left, start, parent);
  if(is_success(left_result)) {
    return left_result;
  }

  parse_result_free(left_result);

  parse_result_t *right_result = parse_dispatch(source, right, start, parent);
  return right_result;
}

parse_result_t *parse_zero_or_more(char *source, expr_t *expr, size_t start, parse_result_t *parent) {
  if(!expr) {
    fatal_error("Can't parse zero-or-more with NULL expression");
  }

  size_t offset = start;
  parse_result_t *result = NULL;

  while((result = parse_dispatch(source, expr, offset, parent)) && is_success(result)) {
    offset += result->data.result->length;
  }

  parse_result_t *ret = is_success(result) ? result : make_result(parse_init("__plus_end", offset, 0));
  ret->data.result->length = offset - start;
  return ret;
}

parse_result_t *parse_one_or_more(char *source, expr_t *expr, size_t start, parse_result_t *parent) {
  if(!expr) {
    fatal_error("Can't parse one-or-more with NULL expression");
  }

  size_t offset = start;
  parse_result_t *result, *prev = NULL;

  while((result = parse_dispatch(source, expr, offset, parent)) && is_success(result)) {
    prev = result;
    offset += result->data.result->length;
  }

  if(prev) {
    prev->data.result->length = offset - start;
  }

  return prev;
}

parse_result_t *parse_optional(char *source, expr_t *expr, size_t start, parse_result_t *parent) {
  if(!expr) {
    fatal_error("Can't parse optional with NULL expression");
  }

  parse_result_t *result = parse_dispatch(source, expr, start, parent);
  return is_success(result) ? result : make_result(parse_init("__optional", start, 0));
}

parse_result_t *parse_and(char *source, expr_t *expr, size_t start) {
  if(!expr) {
    fatal_error("Can't parse logical and with NULL expression");
  }

  parse_result_t *result = parse_dispatch(source, expr, start, NULL);

  if(is_success(result)) {
    return make_result(parse_init("__and", start, 0));
  }

  return result;
}

parse_result_t *parse_not(char *source, expr_t *expr, size_t start) {
  if(!expr) {
    fatal_error("Can't parse logical not with NULL expression");
  }

  parse_result_t *result = parse_dispatch(source, expr, start, NULL);
  if(is_success(result)) {
    return make_error(parse_error_init("Matched expression when not expecting to"));
  }

  return make_result(parse_init("__not", start, 0));
}

#ifndef PARSER_P_H
#define PARSER_P_H

#include "parser.h"

parse_t *parse_dispatch(char *source, expr_t *rule, size_t start, parse_t *parent);
parse_t *parse_empty(char *source, size_t start, parse_t *parent);
parse_t *parse_terminal(char *source, char *symbol, size_t start, parse_t *parent);
parse_t *parse_non_terminal(char *source, char *symbol, size_t start, parse_t *parent);
parse_t *parse_sequence(char *source, expr_t *left, expr_t *right, size_t start, parse_t *parent);
parse_t *parse_choice(char *source, expr_t *left, expr_t *right, size_t start, parse_t *parent);
parse_t *parse_zero_or_more(char *source, expr_t *expr, size_t start, parse_t *parent);
parse_t *parse_one_or_more(char *source, expr_t *expr, size_t start, parse_t *parent);
parse_t *parse_optional(char *source, expr_t *expr, size_t start, parse_t *parent);
parse_t *parse_and(char *source, expr_t *expr, size_t start);
parse_t *parse_not(char *source, expr_t *expr, size_t start);

#endif

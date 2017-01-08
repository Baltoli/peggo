#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include "parse_tree.h"

parse_t *parse(char *source, grammar_t *grammar);
parse_t *parse_dispatch(char *source, expr_t *rule, size_t start, parse_t *parent);
parse_t *parse_empty(char *source, size_t start, parse_t *parent);
parse_t *parse_terminal(char *source, char *symbol, size_t start, parse_t *parent);
parse_t *parse_non_terminal(char *source, char *symbol, size_t start, parse_t *parent);
parse_t *parse_sequence(char *source, expr_t *left, expr_t *right, size_t start, parse_t *parent);
parse_t *parse_choice(char *source, expr_t *left, expr_t *right, size_t start, parse_t *parent);

#endif

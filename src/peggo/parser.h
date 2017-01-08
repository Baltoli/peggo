#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include "parse_tree.h"

parse_t *parse(char *source, grammar_t *grammar);
parse_t *parse_empty(char *source, size_t start, parse_t *parent);
parse_t *parse_terminal(char *source, char *symbol, size_t start, parse_t *parent);

#endif

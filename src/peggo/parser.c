#include <stdlib.h>
#include <string.h>

#include "parser.h"

parse_t *parse(char *source, grammar_t *grammar) {
  // TODO
  parse_t *parent = parse_init("Start", 0, 0);
  return parse_dispatch(source, NULL, 0, parent);
}

parse_t *parse_dispatch(char *source, expr_t *rule, size_t start, parse_t *parent) {
  // TODO
  switch(rule->type) {
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
  // TODO: this needs to do quite a lot of work:
  //        - Needs to get the rule from somewhere. We have the grammar at the
  //          start of parsing, but this would need to be passed around a lot.
  //          One option is to make the parser non-thread safe and just have a
  //          static variable in the parser that contains a mapping from symbols
  //          to rules. This is also the point at which the grammar could be
  //          checked for validity (every non-terminal used needs a production
  //          rule).
  //        - Given a rule, needs to parse it. We should write a generic
  //          dispatcher for expression node types. Parsing a sub-node of an
  //          expression will basically amount to looking up what the type is,
  //          then calling the appropriate parsing methods with the newly
  //          constructed parent node.
  //        - Remember: no other node type should modify the recursive parameter
  //          parent, only non-terminal. All others end up in a flat structure.
  return NULL;
}

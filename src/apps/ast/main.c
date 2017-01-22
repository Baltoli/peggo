#include <stdio.h>

#include "arith_grammar.h"
#include "ast.h"
#include "peggo.h"

ast_t *parse_extract(char *s, grammar_t *g) {
  print_parse(parse(s, g));
  return extract(s, parse(s, g));
}

int main(int argc, char **argv) {
  char *source = argv[1];
  ast_t *a = parse_extract(source, arith_grammar());
  print_ast(a);
  printf("%lld\n", eval(a));
  return 0;
}

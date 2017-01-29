#include <stdio.h>

#include "arith_grammar.h"
#include "ast.h"
#include "peggo.h"

ast_t *parse_extract(char *s, grammar_t *g) {
  parse_t *result = parse(s, g);

  print_parse(result);
  ast_t *a = extract(s, result);
  
  parse_free(result);
  return a;
}

int main(int argc, char **argv) {
  char *source = argv[1];
  ast_t *a = parse_extract(source, arith_grammar());
  print_ast(a);
  printf("%lld\n", eval(a));
  return 0;
}

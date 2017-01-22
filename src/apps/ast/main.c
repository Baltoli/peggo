#include "arith_grammar.h"
#include "ast.h"
#include "peggo.h"

ast_t *parse_extract(char *s, grammar_t *g) {
  return extract(s, parse(s, g));
}

int main(void) {
  char *source = "(-4*(1+2)+3)";
  print_ast(parse_extract(source, arith_grammar()));
  return 0;
}

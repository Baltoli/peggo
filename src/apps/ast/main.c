#include "arith_grammar.h"
#include "ast.h"
#include "peggo.h"

int main(void) {
  char *source = "(-4*(1+2)+3)";
  parse_t *result = parse(source, arith_grammar());
  ast_t *a = extract(source, result);
  print_ast(a);
  return 0;
}

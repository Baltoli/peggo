#include <stdio.h>

#include "arith_grammar.h"
#include "ast.h"
#include "log.h"
#include "peggo.h"

ast_t *parse_extract(char *s, grammar_t *g) {
  parse_result_t *result = parse(s, g);

  if(is_success(result)) {
    print_parse(result->data.result);

    ast_t *a = extract(s, result->data.result);
    parse_result_free(result);
    return a;
  } else {
    fatal_error(result->data.error->message);
  }
  
}

int main(int argc, char **argv) {
  char *source = argv[1];
  ast_t *a = parse_extract(source, arith_grammar());
  print_ast(a);
  printf("%lld\n", eval(a));
  return 0;
}

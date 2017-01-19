#include "arith_grammar.h"
#include "peggo.h"

int main(void) {
  print_grammar(arith_grammar());
  char *source = "1*(2+3*4)*12+(-48)";
  parse_t *result = parse(source, arith_grammar());
  print_parse(result);
  return 0;
}

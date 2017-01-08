#include <stdio.h>
#include <string.h>

#include "peggo/grammar.h"
#include "peggo/parse_tree.h"
#include "peggo/parser.h"

int main(int argc, char **argv) {
  rule_t *digit = rule_init("Digit", 
    choice(
      terminal("0"), choice(
      terminal("1"), choice(
      terminal("2"), choice(
      terminal("3"), choice(
      terminal("4"), choice(
      terminal("5"), choice(
      terminal("6"), choice(
      terminal("7"), choice(
      terminal("8"), 
      terminal("9")))))))))
    )
  );

  rule_t *sign = rule_init("Sign",
    choice(
      terminal("+"),
      terminal("-")
    )
  );

  rule_t *number = rule_init("Number",
    sequence(
      optional(non_terminal("Sign")),
      one_or_more(non_terminal("Digit"))
    )
  );

  rule_t *start = rule_init("Start", non_terminal("Number"));

  rule_t rules[] = {
    *digit, *start, *sign, *number
  };

  grammar_t *gram = grammar_init(non_terminal("Start"), rules, 4);
  print_grammar(gram);

  char *source = "+91234";
  parse_t *result = parse(source, gram);

  if(result && result->length != strlen(source)) {
    printf("Didn't consume the full input\n");
  }

  print_parse(result);
  return 0;
}

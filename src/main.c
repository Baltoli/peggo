#include "peggo/grammar.h"
#include "peggo/parse_tree.h"
#include "peggo/parser.h"

int main(int argc, char **argv) {
  expr_t *start_e = non_terminal("World");
  rule_t *start = rule_init("Start", start_e);
  
  expr_t *world_e = terminal("world");
  rule_t *world = rule_init("World", world_e);

  rule_t rules[2] = {
    *start, *world
  };

  grammar_t *gram = grammar_init(non_terminal("Start"), rules, 2);
  print_grammar(gram);

  char *source = "world";
  parse_t *result = parse(source, gram);
  print_parse(result);
  return 0;
}

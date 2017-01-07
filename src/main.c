#include "peggo/grammar.h"
#include "peggo/parse_tree.h"

int main(int argc, char **argv) {
  expr_t *g = 
    sequence(
      and(
        not(non_terminal("err")),
        not(non_terminal("woo"))
      ),
      terminal("hello")
    );
  rule_t *rule = rule_init("sym", g);
  grammar_t *gram = grammar_init(non_terminal("sym"), rule, 1);
  print_grammar(gram);

  parse_t *tree = parse_init("Start", 0, 3);
  parse_add_child(tree, parse_init("Digit", 0, 1));
  parse_add_child(tree, parse_init("Digit", 1, 1));
  parse_add_child(tree, parse_init("Digit", 2, 1));
  print_parse(tree);
  parse_free(tree);
  return 0;
}

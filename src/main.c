#include "peggo/grammar.h"
#include "peggo/parse_tree.h"

int main(int argc, char **argv) {
  peg_expr_t *g = 
    peg_sequence(
      peg_and(
        peg_not(peg_non_terminal("err")),
        peg_not(peg_non_terminal("woo"))
      ),
      peg_terminal("hello")
    );
  peg_rule_t *rule = peg_rule_init("sym", g);
  peg_grammar_t *gram = peg_grammar_init(peg_non_terminal("sym"), rule, 1);
  peg_print_grammar(gram);

  peg_parse_t *tree = peg_parse_init("Start", 0, 3);
  peg_parse_add_child(tree, peg_parse_init("Digit", 0, 1));
  peg_parse_add_child(tree, peg_parse_init("Digit", 1, 1));
  peg_parse_add_child(tree, peg_parse_init("Digit", 2, 1));
  peg_print_parse(tree);
  peg_parse_free(tree);
  return 0;
}

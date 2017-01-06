#include "peggo/rule.h"

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
  peg_print_rule(rule);

  peg_rule_free(rule);
  return 0;
}

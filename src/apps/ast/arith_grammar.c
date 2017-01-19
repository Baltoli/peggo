#include <stdlib.h>

#include "arith_grammar.h"

grammar_t *arith_grammar() {
  rule_t *rules = malloc(sizeof(*rules) * 9);

  rules[0] = *digit();
  rules[1] = *sign();
  rules[2] = *number();
  rules[3] = *value();

  rules[4] = *add_op();
  rules[5] = *mul_op();

  rules[6] = *product();
  rules[7] = *sum();
  rules[8] = *expr();

  return grammar_init(
      non_terminal("Expr"),
      rules, 9);
}

rule_t *digit() {
  return rule_init("Digit",
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
        terminal("9")
      ))))))))));
}

rule_t *sign() {
  return rule_init("Sign",
      choice(
        terminal("-"),
        terminal("+")
      ));
}

rule_t *number() {
  return rule_init("Number",
      sequence(
        optional(non_terminal("Sign")),
        one_or_more(non_terminal("Digit"))
      ));
}

rule_t *value() {
  return rule_init("Value",
      choice(
        non_terminal("Number"),
        sequence(
          terminal("("), sequence(
          non_terminal("Expr"),
          terminal(")")
        ))
      ));
}

rule_t *add_op() {
  return rule_init("AddOp",
      choice(
        terminal("+"),
        terminal("-")
      ));
}

rule_t *mul_op() {
  return rule_init("MulOp",
      choice(
        terminal("*"),
        terminal("-")
      ));
}

rule_t *product() {
  return rule_init("Product",
      sequence(
        non_terminal("Value"),
        zero_or_more(
          sequence(
            non_terminal("MulOp"),
            non_terminal("Value")
          )
        )
      ));
}

rule_t *sum() {
  return rule_init("Sum",
      sequence(
        non_terminal("Product"),
        zero_or_more(
          sequence(
            non_terminal("AddOp"),
            non_terminal("Product")
          )
        )
      ));
}

rule_t *expr() {
  return rule_init("Expr",
      non_terminal("Sum"));
}

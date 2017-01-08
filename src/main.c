#include "peggo/grammar.h"
#include "peggo/parse_tree.h"
#include "peggo/parser.h"

int main(int argc, char **argv) {
  expr_t *whitespace = one_or_more(
    choice(
      terminal(" "),
      terminal("\t")
    )
  );

  expr_t *start_e =
    sequence(
      sequence(
        optional(whitespace),
        terminal("y")
      ),
      terminal("hello")
    );
  rule_t *start = rule_init("Start", start_e);
  
  expr_t *world_e = terminal("world");
  rule_t *world = rule_init("World", world_e);

  expr_t *thing_e = non_terminal("World");
  rule_t *thing = rule_init("Thing", sequence(thing_e, empty()));

  rule_t rules[3] = {
    *start, *world, *thing
  };

  grammar_t *gram = grammar_init(non_terminal("Start"), rules, 3);
  print_grammar(gram);
  char *source = "\t     yhello";
  parse_t *result = parse(source, gram);
  print_parse(result);
  return 0;
}

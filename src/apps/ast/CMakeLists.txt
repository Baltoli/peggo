add_executable(ast
  main.c
  arith_grammar.c
  ast.c
)
target_link_libraries(ast peggo)

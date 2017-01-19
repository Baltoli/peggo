add_executable(ast
  main.c
  arith_grammar.c
)
target_link_libraries(ast peggo)

add_executable(unit_tests 
  main.c
  test_parser.c
)
target_link_libraries(unit_tests cmocka peggo)

cmake_minimum_required(VERSION 3.4.3)
project(Peggo)

add_subdirectory(src/peggo)

add_executable(main
  src/main.c
)

target_link_libraries(main
  peggo
)

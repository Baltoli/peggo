cmake_minimum_required(VERSION 2.8)
project(Peggo)

find_package(cmocka)
if(${cmocka_FOUND})
  include_directories(${CMOCKA_INCLUDE_DIR})
  enable_testing()
  message(STATUS "Found cmocka, enabling unit tests")
  add_subdirectory(test)
endif()

set(VERSION_MAJOR 0)
set(VERSION_MINOR 3)
set(VERSION_PATCH 0)
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

include_directories(src/lib)

add_subdirectory(src)
add_subdirectory(docs)

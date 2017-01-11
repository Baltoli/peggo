cmake_minimum_required(VERSION 2.8)
project(Peggo)

find_package(cmocka)
if(${cmocka_FOUND})
  message(STATUS "Found cmocka, enabling unit tests")
  add_subdirectory(test)
endif()

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

add_subdirectory(src)
add_subdirectory(docs)

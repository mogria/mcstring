cmake_minimum_required(VERSION 2.8)

project(mcstring)

file(GLOB_RECURSE MCSTRING_SOURCE_FILES "src/*.c")
file(GLOB_RECURSE MCSTRING_TEST_FILES "test/*.c")

set(CMAKE_C_FLAGS "-g -Wall")

include_directories(${PROJECT_BINARY_DIR}/include)

add_library("mcstring" ${MCSTRING_SOURCE_FILES})

IF(NOT MCSTRING_NOTEST)
  add_executable("mcstring_test" ${MCSTRING_TEST_FILES})
  target_link_libraries("mcstring_test" "mcstring")
ENDIF()

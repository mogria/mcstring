cmake_minimum_required(VERSION 2.8)

project(mcstring)

file(GLOB_RECURSE MCSTRING_SOURCE_FILES "src/*.c")

set (CMAKE_C_FLAGS "-g -Wall")

include_directories(${PROJECT_BINARY_DIR}/include)

add_library("cstring" ${MCSTRING_SOURCE_FILES})

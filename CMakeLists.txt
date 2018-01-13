cmake_minimum_required(VERSION 3.2)

project(TheOS LANGUAGES CXX ASM_NASM)

# Add include directory
include_directories("${PROJECT_SOURCE_DIR}/include")

option(SKIP_TEST "True to skip unit tests after build")

# Add flags to the C++ compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Place the executable files in the root directory instead of in test
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(test)

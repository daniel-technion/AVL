cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

project(AVL VERSION 0.1.0 LANGUAGES CXX)

# If you want to see "under the hood" of CMake, uncomment this:

# set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")

set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(idkbruh main.cpp AVL.cpp Node.cpp)
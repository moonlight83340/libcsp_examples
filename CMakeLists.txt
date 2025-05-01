cmake_minimum_required(VERSION 3.10)
project(libcsp_examples C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)

find_package(Threads REQUIRED)

# Add libcsp
add_subdirectory(libcsp)

# Add examples
add_subdirectory(utils)
add_subdirectory(examples)

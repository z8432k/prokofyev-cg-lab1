cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(prokofyev-cg-lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Detected GNU compiler. Using specific flags.")
    set(CMAKE_CXX_FLAGS "-pipe -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -O0 -ggdb3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_subdirectory(src)

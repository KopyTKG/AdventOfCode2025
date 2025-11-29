cmake_minimum_required(VERSION 4.1)

project(
	AdventOfCode2025
	VERSION "0.1.0"
	DESCRIPTION "C++23 project for solving Advent of Code 2025 challenges"
	LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.11.0
)

FetchContent_MakeAvailable(Catch2)

include(CTest)

add_subdirectory(src)




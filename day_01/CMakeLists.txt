project(aoc-2021 DESCRIPTION "Advent of Code 2021")

add_executable(day01 solution.cpp)
set_property(TARGET day01 PROPERTY CXX_STANDARD 20)
target_include_directories(day01 PRIVATE "$CMAKE_CURRENT_SOURCE_DIR")


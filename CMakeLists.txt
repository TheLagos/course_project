cmake_minimum_required(VERSION 3.14)
project(course_project)

set(CMAKE_CXX_STANDARD 17)

add_library(SearchLib
	graph_structure.h
	algorithms.h
	algorithms.cpp
 "graph_generator.cpp" "graph_generator.h")

target_include_directories(SearchLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SearchLab main.cpp "graph_generator.cpp" "graph_generator.h")

include(FetchContent)

target_link_libraries(SearchLab PRIVATE SearchLib)

enable_testing()
add_subdirectory(tests)
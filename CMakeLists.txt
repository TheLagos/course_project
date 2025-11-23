cmake_minimum_required(VERSION 3.10)
project(course_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(SearchLab
	main.cpp
	graph_structure.h
	algorithms.h
	algorithms.cpp
)
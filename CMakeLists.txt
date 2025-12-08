cmake_minimum_required(VERSION 3.14)
project(course_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

add_library(SearchLib
	graph_types.h
	algorithms.h algorithms.cpp
	grid.h grid.cpp
)

target_include_directories(SearchLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SearchLab
	main.cpp
	mainwindow.h mainwindow.cpp
	mainwindow.ui
)

target_link_libraries(SearchLab PRIVATE
	Qt6::Widgets
	Qt6::Charts
	SearchLib
)

if(WIN32)
	set_property(TARGET SearchLab PROPERTY WIN32_EXECUTABLE ON)
endif()

enable_testing()
add_subdirectory(tests)

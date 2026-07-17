cmake_minimum_required(VERSION 4.2)

project(little_program)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Release)

find_package(CGAL REQUIRED)

add_executable(little_program
                Asterism.cpp
                Board.cpp
                Board_set.cpp
                Discrete_point.cpp
                State.cpp
                A_star.cpp
                Simulation.cpp
                main.cpp)

target_link_libraries(little_program CGAL::CGAL)
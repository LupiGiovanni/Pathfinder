cmake_minimum_required(VERSION 4.2)

project(little_program)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Release)

find_package(CGAL REQUIRED)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(little_program
                Asterism.cpp
                Board.cpp
                Board_set.cpp
                Discrete_point.cpp
                State.cpp
                A_star.cpp
                Simulation.cpp
                Animation.cpp
                main.cpp)

target_link_libraries(little_program
                        CGAL::CGAL
                        sfml-graphics
                        sfml-window
                        sfml-system)
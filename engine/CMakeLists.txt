cmake_minimum_required(VERSION 3.12)

project(engine)

set (CMAKE_CXX_STANDARD 14)

add_executable(cube_no_fill ../gl/gl.cpp cube_no_fill.cpp)
add_executable(cube_fill ../gl/gl.cpp cube_fill.cpp)
add_executable(spaceship ../gl/gl.cpp spaceship.cpp)
cmake_minimum_required(VERSION 3.12)

project(engine)

set (CMAKE_CXX_STANDARD 14)

add_executable(engine ../gl/gl.cpp engine.cpp)
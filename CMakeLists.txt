cmake_minimum_required(VERSION 3.0)
project(SimpleGraph)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(SimpleGraph ${SOURCES})
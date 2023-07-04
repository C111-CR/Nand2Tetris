cmake_minimum_required(VERSION 3.21)
project(hack_assembler)

set(CMAKE_CXX_STANDARD 17)

set( CMAKE_BUILD_TYPE "Debug" )

add_executable(hack_assembler hack_assembler.cpp)

# CMakeList.txt : CMake project for cpp_cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library(include INTERFACE)
target_include_directories(include INTERFACE ./asio)
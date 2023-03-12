# CMakeList.txt : CMake project for cpp_cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library(network INTERFACE)
target_include_directories(network INTERFACE .)

# third party dependencies
target_link_libraries(network INTERFACE include)

# target feature
target_compile_features(network INTERFACE cxx_std_17)
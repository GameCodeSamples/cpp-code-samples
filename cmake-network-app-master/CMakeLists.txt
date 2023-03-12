# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("cpp_cmake")

# Include sub-projects.
add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (examples/client)
add_subdirectory (examples/multiclient)
add_subdirectory (examples/server)

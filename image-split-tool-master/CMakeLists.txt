cmake_minimum_required(VERSION 3.8)

project(image-split-tool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

# # GLEW
# set(GLEW_INCLUDE_DIR "C:/Program Files/vcpkg/packages/glew_x86-windows/include")
# set(GLEW_LIBRARY "C:/Program Files/vcpkg/packages/glew_x86-windows/debug/lib")
find_package(GLEW REQUIRED)

# GLFW
find_package(glfw3 CONFIG REQUIRED)

# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)

# Native dialog
# set(NATIVEDIALOG_INCLUDE "/home/tia/c_libs/nativefiledialog-release_116/src/include")
# set(NATIVEDIALOG_LIB "/home/tia/c_libs/nativefiledialog-release_116/build/lib/Release/x64/libnfd.a")
find_package(unofficial-nativefiledialog CONFIG REQUIRED)

# Includes
include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${NATIVEDIALOG_INCLUDE}
        external/source/imgui
        external/source
        src)

# Executable
add_executable(image-split-tool
        src/main.cpp
        src/app.cpp
        external/source/imgui/imgui.cpp
        external/source/imgui/imgui_demo.cpp
        external/source/imgui/imgui_draw.cpp
        external/source/imgui/imgui_tables.cpp
        external/source/imgui/imgui_widgets.cpp
        external/source/imgui/imgui_impl_opengl3.cpp
        external/source/imgui/imgui_impl_glfw.cpp)

# Link libraries to executable
target_link_libraries(image-split-tool ${OpenCV_LIBS} unofficial::nativefiledialog::nfd GLEW::GLEW glfw)

 ## Copy assets into build
 add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Copying assets to ${CMAKE_CURRENT_BINARY_DIR}") 
# Overview

Implementation of a simple image splitting tool in C++ and using ImGui.

# Install

## Windows use VcPkg toolchain with cmake

1. Configure CMake to use x64 architecture
Add this environment variable to your system:
```
VCPKG_DEFAULT_TRIPLET=x64-windows

// add this tu .vscode/settings.json
"cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake",
        "VCPKG_TARGET_TRIPLET": "x64-windows"
}

```

2. Tell Cmake use VcPkg

Cmake: Configure Args
Additional arguments to pass to CMake when configuring.

-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake

3. Install packages

```
vcpgk install
```

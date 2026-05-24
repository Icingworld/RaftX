cmake_minimum_required(VERSION 4.3.0)

# See https://www.kitware.com/import-std-in-cmake-3-30/
# UUID for CMake 4.3.x — see https://github.com/Kitware/CMake/blob/v4.3.2/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

project(raftx VERSION 0.1.0 LANGUAGES CXX)

# C++26
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSIONS ON)

# add source files
## modules
### memory
add_library(raftx_memory)
target_sources(raftx_memory
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
            modules/memory/include/free_list.ixx
    PRIVATE
        modules/memory/src/free_list.cpp
)

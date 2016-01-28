cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

project(csvgrep)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

set_property(TARGET csvgrep PROPERTY C_STANDARD 99)

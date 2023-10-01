cmake_minimum_required(VERSION 3.5)
project(heart_raylib_input VERSION 1.0.0)

include(../ModuleHelper.cmake)

add_library(heart_raylib_input src/raylib_input.cpp)
target_include_directories(heart_raylib_input PUBLIC include)

FetchLibraryGit(heart_raylib_input raylib https://github.com/raysan5/raylib.git ${RAYLIB_VERSION})
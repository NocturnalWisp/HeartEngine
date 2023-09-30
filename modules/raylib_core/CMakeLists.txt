cmake_minimum_required(VERSION 3.5)
project(heart_raylib_core VERSION 1.0.0)

option(RAYLIB_VERSION 4.5.0)

include(../ModuleHelper.cmake)

include_directories(include)
add_library(heart_raylib_core src/raylib_core.cpp)

FetchLibraryGit(heart_raylib_core raylib https://github.com/raysan5/raylib.git ${RAYLIB_VERSION})
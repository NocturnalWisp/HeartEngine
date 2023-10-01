cmake_minimum_required(VERSION 3.5)
project(heart_raymath VERSION 1.0.0)

include(../../tools/ModuleHelper.cmake)

add_library(heart_raymath src/raymath.cpp)
target_include_directories(heart_raymath PUBLIC include)

FetchLibraryGit(heart_raymath raylib https://github.com/raysan5/raylib.git ${RAYLIB_VERSION})

LinkLibrary(heart_raymath HeartEngine)
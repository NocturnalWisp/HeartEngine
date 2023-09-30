cmake_minimum_required(VERSION 3.5)
project(heart_raylib_input VERSION 1.0.0)

include(../ModuleHelper.cmake)

include_directories(include)
add_library(heart_raylib_input src/raylib_input.cpp)
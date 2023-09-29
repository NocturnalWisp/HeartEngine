cmake_minimum_required(VERSION 3.5)
project(LuaGame)

set(USE_EDITOR OFF)

include(Main.cmake)

# Raymath
load_module(modules/raymath modules/raymath/include heart_raymath)

add_executable(${PROJECT_NAME} main.cpp)
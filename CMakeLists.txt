cmake_minimum_required(VERSION 3.5)
project(LuaGame)

set(USE_EDITOR OFF)

include(Main.cmake)

# Raymath
load_module(modules/raymath modules/raymath/include heart_raymath)
# Transforms
load_module(modules/transforms modules/transforms/include heart_transforms)

include_directories(include)
add_executable(${PROJECT_NAME} main.cpp)
cmake_minimum_required(VERSION 3.5)
project(LuaGame)

set(RAYLIB_VERSION 4.5.0)
set(USE_EDITOR OFF)

include(Main.cmake)

# Raylib Core
load_module(modules/raylib_core modules/raylib_core/include heart_raylib_core)
# Raymath
load_module(modules/raymath modules/raymath/include heart_raymath)
# Raylib Input
load_module(modules/raylib_input modules/raylib_input/include heart_raylib_input)
# Raylib Textures
load_module(modules/raylib_textures modules/raylib_textures/include heart_raylib_textures)

# Transforms
load_module(modules/transforms modules/transforms/include heart_transforms)

include_directories(include)
add_executable(${PROJECT_NAME} main.cpp)
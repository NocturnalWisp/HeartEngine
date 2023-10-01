cmake_minimum_required(VERSION 3.5)
project(LuaGame)

set(RAYLIB_VERSION 4.5.0)
set(USE_EDITOR OFF)

include(Main.cmake)

include_directories(include)
add_executable(${PROJECT_NAME} main.cpp)

# Heart Engine
LoadModule(${PROJECT_NAME} core include HeartEngine)

# Raylib Core
LoadModule(${PROJECT_NAME} modules/raylib_core include heart_raylib_core)
# Raymath
LoadModule(${PROJECT_NAME} modules/raymath include heart_raymath)
# Raylib Input
LoadModule(${PROJECT_NAME} modules/raylib_input include heart_raylib_input)
# Raylib Textures
LoadModule(${PROJECT_NAME} modules/raylib_textures include heart_raylib_textures)

# Transforms
LoadModule(${PROJECT_NAME} modules/transforms include heart_transforms)

# Drawables
LoadModule(${PROJECT_NAME} modules/drawables include heart_drawables)
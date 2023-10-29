cmake_minimum_required(VERSION 3.5)
project(heart_raylib_input VERSION 1.0.0)

option(RAYINPUT_INCLUDE_KEYBOARD "Lua bindings for keyboard input." ON)
option(RAYINPUT_INCLUDE_MOUSE "Lua bindings for mouse input." ON)
option(RAYINPUT_INCLUDE_GAMEPAD "Lua bindings for game pad input." OFF)
option(RAYINPUT_INCLUDE_TOUCH "Lua bindings for touch input." OFF)

add_library(heart_raylib_input src/raylib_input.cpp)
target_include_directories(heart_raylib_input PUBLIC include)

if(RAYINPUT_INCLUDE_KEYBOARD)
    target_compile_definitions(heart_raylib_input PUBLIC INCLUDE_KEYBOARD)
endif()
if(RAYINPUT_INCLUDE_MOUSE)
    target_compile_definitions(heart_raylib_input PUBLIC INCLUDE_MOUSE)
endif()
if(RAYINPUT_INCLUDE_GAMEPAD)
    target_compile_definitions(heart_raylib_input PUBLIC INCLUDE_GAMEPAD)
endif()
if(RAYINPUT_INCLUDE_TOUCH)
    target_compile_definitions(heart_raylib_input PUBLIC INCLUDE_TOUCH)
endif()

FetchLibraryGit(heart_raylib_input raylib https://github.com/raysan5/raylib.git 4.3.0)
FetchLibraryGit(heart_raylib_input raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raylib_input HeartEngine core/include)
LinkLibrary(heart_raylib_core HeartEngine core/include)
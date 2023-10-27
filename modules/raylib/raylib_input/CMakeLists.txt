cmake_minimum_required(VERSION 3.5)
project(heart_raylib_input VERSION 1.0.0)

add_library(heart_raylib_input src/raylib_input.cpp)
target_include_directories(heart_raylib_input PUBLIC include)

FetchLibraryGit(heart_raylib_input raylib https://github.com/raysan5/raylib.git 4.3.0)
FetchLibraryGit(heart_raylib_input raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raylib_input HeartEngine core/include)
LinkLibrary(heart_raylib_core HeartEngine core/include)
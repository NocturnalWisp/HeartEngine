cmake_minimum_required(VERSION 3.5)
project(heart_raylib_shapes VERSION 1.0.0)

add_library(heart_raylib_shapes src/raylib_shapes.cpp)
target_include_directories(heart_raylib_shapes PUBLIC include)

FetchLibraryGit(heart_raylib_shapes raylib https://github.com/raysan5/raylib.git 4.5.0)
FetchLibraryGit(heart_raylib_shapes raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raylib_shapes HeartEngine core/include)
LinkLibrary(heart_raylib_shapes heart_raylib_core include)
cmake_minimum_required(VERSION 3.5)
project(heart_raylib_drawables VERSION 1.0.0)

add_library(heart_raylib_drawables src/raylib_drawables.cpp)
target_include_directories(heart_raylib_drawables PUBLIC include)

FetchLibraryGit(heart_raylib_drawables raylib https://github.com/raysan5/raylib.git 4.3.0)
FetchLibraryGit(heart_raylib_drawables raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raylib_drawables heart_raylib_textures include)
LinkLibrary(heart_raylib_drawables heart_raylib_transforms include)
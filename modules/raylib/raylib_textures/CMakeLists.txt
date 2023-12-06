cmake_minimum_required(VERSION 3.5)
project(heart_raylib_textures VERSION 1.0.0)

set(RAYLIB_CPP_VERSION 4.5.0)

add_library(heart_raylib_textures src/raylib_textures.cpp)
target_include_directories(heart_raylib_textures PUBLIC include)

FetchLibraryGit(heart_raylib_textures raylib https://github.com/raysan5/raylib.git 4.5.0)
FetchLibraryGit(heart_raylib_textures raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raylib_textures HeartEngine core/include)
LinkLibrary(heart_raylib_textures heart_raylib_core include)
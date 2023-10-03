cmake_minimum_required(VERSION 3.5)
project(heart_raylib_drawables VERSION 1.0.0)

include(../../tools/ModuleHelper.cmake)

add_library(heart_raylib_drawables src/raylib_drawables.cpp)
target_include_directories(heart_raylib_drawables PUBLIC include)

FetchLibraryGit(heart_raylib_drawables raylib https://github.com/raysan5/raylib.git ${RAYLIB_VERSION})
FetchLibraryGit(heart_raylib_drawables raylib_cpp https://github.com/RobLoach/raylib-cpp.git v${RAYLIB_CPP_VERSION})

LinkLibrary(heart_raylib_drawables heart_raylib_textures)
LinkLibrary(heart_raylib_drawables heart_transforms)
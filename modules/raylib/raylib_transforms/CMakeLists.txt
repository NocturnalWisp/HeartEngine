cmake_minimum_required(VERSION 3.5)
project(heart_raylib_transforms VERSION 1.0.0)

add_library(heart_raylib_transforms src/raylib_transforms.cpp)
target_include_directories(heart_raylib_transforms PUBLIC include)

FetchLibraryGit(heart_raylib_transforms raylib https://github.com/raysan5/raylib.git 4.3.0)
FetchLibraryGit(heart_raylib_transforms raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raylib_transforms HeartEngine core/include)
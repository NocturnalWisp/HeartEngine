cmake_minimum_required(VERSION 3.5)
project(heart_transforms VERSION 1.0.0)

add_library(heart_transforms
    src/transforms.cpp
    src/transform_3d.cpp
)
target_include_directories(heart_transforms PUBLIC include)

FetchLibraryGit(heart_transforms raylib https://github.com/raysan5/raylib.git 4.3.0)

LinkLibrary(heart_transforms HeartEngine core/include)
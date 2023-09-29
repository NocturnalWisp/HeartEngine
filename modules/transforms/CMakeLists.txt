cmake_minimum_required(VERSION 3.5)
project(heart_raymath VERSION 1.0.0)

include(../ModuleHelper.cmake)

include_directories(include)
add_library(heart_transforms src/transforms.cpp
    src/transform_3d.cpp
)
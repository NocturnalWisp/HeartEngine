cmake_minimum_required(VERSION 3.5)
project(heart_raylib_core VERSION 1.0.0)

set(RAYLIB_VERSION 4.5.0)

add_library(heart_raylib_core
    src/raylib_core.cpp
    src/camera2d.cpp
)
target_include_directories(heart_raylib_core PUBLIC include)

FetchLibraryGit(heart_raylib_core raylib https://github.com/raysan5/raylib.git ${RAYLIB_VERSION})
FetchLibraryGit(heart_raylib_core raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

target_compile_definitions(raylib PUBLIC SUPPORT_CUSTOM_FRAME_CONTROL=1)

LinkLibrary(heart_raylib_core HeartEngine core/include)
cmake_minimum_required(VERSION 3.5)
project(heart_raylib_gui VERSION 1.0.0)

add_library(heart_raylib_gui src/raylib_gui.cpp)
target_include_directories(heart_raylib_gui PUBLIC include)

FetchLibraryGit(heart_raylib_gui raylib https://github.com/raysan5/raylib.git 4.5.0)
FetchLibraryGit(heart_raylib_gui raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

FetchLibraryGit(heart_raylib_gui raygui https://github.com/raysan5/raygui.git 4.0)
FetchContent_GetProperties(raygui)
add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake
    ${raygui_BINARY_DIR})

LinkLibrary(heart_raylib_gui HeartEngine core/include)
LinkLibrary(heart_raylib_gui heart_raylib_core include)
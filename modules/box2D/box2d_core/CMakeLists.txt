cmake_minimum_required(VERSION 3.5)
project(heart_box2d_core VERSION 1.0.0)

add_library(heart_box2d_core src/box2d_core.cpp)
target_include_directories(heart_box2d_core PUBLIC include)

set(BOX2D_BUILD_UNIT_TESTS OFF)
set(BOX2D_BUILD_TESTBED OFF)
set(BOX2D_BUILD_DOCS OFF)
set(BOX2D_USER_SETTINGS OFF)

# Include libraries here using FetchLibraryGit.
FetchLibraryGit(heart_box2d_core box2d https://github.com/erincatto/box2d.git v2.4.0)

LinkLibrary(heart_box2d_core HeartEngine core/include)
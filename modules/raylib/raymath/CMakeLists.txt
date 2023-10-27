cmake_minimum_required(VERSION 3.5)
project(heart_raymath VERSION 1.0.0)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
if (CMAKE_BUILD_TYPE STREQUAL  "")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
endif()

add_library(heart_raymath src/raymath.cpp)
target_include_directories(heart_raymath PUBLIC include)

FetchLibraryGit(heart_raymath raylib https://github.com/raysan5/raylib.git 4.3.0)
FetchLibraryGit(heart_raymath raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

LinkLibrary(heart_raymath HeartEngine core/include)
LinkLibrary(heart_raymath heart_raylib_core include)
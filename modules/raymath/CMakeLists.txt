cmake_minimum_required(VERSION 3.12)
project(heart_raymath VERSION 1.0.0)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../core")

find_package(LuaEngine REQUIRED)

add_library(heart_raymath INTERFACE)

target_include_directories(heart_raymath INTERFACE .)

target_include_directories(heart_raymath INTERFACE ${LuaEngine_INCLUDE_DIR}/include)

target_link_libraries(heart_raymath INTERFACE LuaEngine)
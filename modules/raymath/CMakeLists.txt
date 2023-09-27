cmake_minimum_required(VERSION 3.5)
project(heart_raymath VERSION 1.0.0)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Os")

add_library(heart_raymath src/raymath.cpp)

find_library(LuaEngine LuaEngine)

target_include_directories(heart_raymath PUBLIC ${LuaEngine_SOURCE_DIR}/include)

target_include_directories(heart_raymath PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(heart_raymath PUBLIC ${sol2_SOURCE_DIR}/include)

target_link_libraries(heart_raymath sol2::sol2)
target_link_libraries(heart_raymath LuaEngine)
cmake_minimum_required(VERSION 3.12)
project(LuaGame)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp)

include_directories(${PROJECT_NAME} PUBLIC core/include)

target_link_libraries(${PROJECT_NAME} PUBLIC LuaEngine)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)
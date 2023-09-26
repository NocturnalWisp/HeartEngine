cmake_minimum_required(VERSION 3.12)
project(LuaGame)

set(CMAKE_CXX_STANDARD 17)
set(USE_EDITOR OFF)

add_subdirectory(core)
add_subdirectory(modules/raymath)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp)

include_directories(${PROJECT_NAME} PUBLIC core/include)
include_directories(${PROJECT_NAME} PUBLIC modules/raymath/include)

target_link_libraries(${PROJECT_NAME} PUBLIC LuaEngine)
target_link_libraries(${PROJECT_NAME} PUBLIC heart_raymath)

if (USE_EDITOR)
    add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    )
    add_dependencies(${PROJECT_NAME} copy_assets)
else()
    find_package(Python3 REQUIRED)
    add_custom_target(copy_assets
        COMMAND Python3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/ResourcePackager.py
            ${CMAKE_CURRENT_SOURCE_DIR}/tools
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            ${CMAKE_CURRENT_BINARY_DIR}/data.heart)
        add_dependencies(${PROJECT_NAME} copy_assets)
endif()
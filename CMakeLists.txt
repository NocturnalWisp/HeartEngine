cmake_minimum_required(VERSION 3.12)
project(LuaEngine)

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)
add_subdirectory(external/lua)

file(GLOB_RECURSE lua_engine_sources CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${lua_engine_sources})

include_directories(${PROJECT_NAME} PUBLIC include)
include_directories(${PROJECT_NAME} PUBLIC sol)

target_link_libraries(${PROJECT_NAME} PRIVATE lua::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release mode
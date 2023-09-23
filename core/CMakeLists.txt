cmake_minimum_required(VERSION 3.12)
project(LuaEngine)

set(CMAKE_CXX_STANDARD 17)


# Settings
set(SOL_ALL_SAFETIES_ON 1)



# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)
add_subdirectory(libs/lua)

file(GLOB_RECURSE lua_engine_sources CONFIGURE_DEPENDS src/*.cpp)
add_library(LuaEngine ${lua_engine_sources})

target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/libs/sol)
target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/libs)

target_link_libraries(LuaEngine lua::lib)
target_link_libraries(LuaEngine raylib)
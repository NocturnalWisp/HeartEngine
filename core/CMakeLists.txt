cmake_minimum_required(VERSION 3.12)
project(LuaEngine)

cmake_policy(SET CMP0079 NEW)

# Settings
option(USE_EDITOR "Allow for editing game source after compilation." ON)
option(USE_DEBUG "Allow the engine to print to the console." ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 4.5.0)

include(FetchContent)

FetchContent_Declare(lua
  GIT_REPOSITORY     https://github.com/walterschell/Lua.git
  GIT_TAG            v5.4.5
)
FetchContent_MakeAvailable(lua)

FetchContent_Declare(raylib
  GIT_REPOSITORY     https://github.com/raysan5/raylib.git
  GIT_TAG            
  4.5.0
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(raylib_cpp
  GIT_REPOSITORY     https://github.com/RobLoach/raylib-cpp.git
  GIT_TAG            v4.5.0
)
FetchContent_MakeAvailable(raylib_cpp)

FetchContent_Declare(sol2
  GIT_REPOSITORY     https://github.com/ThePhD/sol2.git
  GIT_TAG            v3.3.1
)
FetchContent_MakeAvailable(sol2)

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
# set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
# set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
# set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)

file(GLOB_RECURSE lua_engine_sources CONFIGURE_DEPENDS src/*.cpp)
add_library(LuaEngine ${lua_engine_sources})

if (USE_EDITOR)
    target_compile_definitions(LuaEngine PUBLIC EDITOR)
endif()

if (USE_DEBUG)
    target_compile_definitions(LuaEngine PUBLIC DEBUG)
endif()

target_compile_definitions(LuaEngine PUBLIC SOL_ALL_SAFETIES_ON=1)

target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(LuaEngine PUBLIC ${raylib_SOURCE_DIR}/include)
target_include_directories(LuaEngine PUBLIC ${raylib_cpp_SOURCE_DIR}/include)
target_include_directories(LuaEngine PUBLIC ${sol2_SOURCE_DIR}/include)
target_include_directories(LuaEngine PUBLIC ${lua_SOURCE_DIR}/lua-5.4.5/include)

target_include_directories(sol2 INTERFACE $<BUILD_INTERFACE:${lua_SOURCE_DIR}/lua-5.4.5/include>)

target_link_libraries(LuaEngine lua_static)
target_link_libraries(LuaEngine sol2::sol2)
target_link_libraries(LuaEngine raylib)
target_link_libraries(LuaEngine raylib_cpp)
cmake_minimum_required(VERSION 3.12)
project(LuaEngine)

# Settings
option(USE_EDITOR "Allow for editing game source after compilation." ON)
option(USE_DEBUG "Allow the engine to print to the console." ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/lua)
add_subdirectory(libs/raylib-cpp)

file(GLOB_RECURSE lua_engine_sources CONFIGURE_DEPENDS src/*.cpp)
add_library(LuaEngine ${lua_engine_sources})

if (USE_EDITOR)
    target_compile_definitions(LuaEngine PUBLIC EDITOR)
endif()

if (USE_DEBUG)
    target_compile_definitions(LuaEngine PUBLIC DEBUG)
endif()

target_compile_definitions(LuaEngine PUBLIC SOL_ALL_SAFETIES_ON=1)

target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/libs/sol)
target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/libs)
target_include_directories(LuaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/libs/raylib-cpp/include)

target_link_libraries(LuaEngine lua::lib)
target_link_libraries(LuaEngine raylib)
target_link_libraries(LuaEngine raylib_cpp)
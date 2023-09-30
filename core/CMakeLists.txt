cmake_minimum_required(VERSION 3.5)
project(HeartEngine)

cmake_policy(SET CMP0079 NEW)
cmake_policy(SET CMP0077 NEW)

set(CMAKE_CXX_STANDARD 17)

# Settings
option(USE_EDITOR "Allow for editing game source after compilation." ON)
option(USE_DEBUG "Allow the engine to print to the console." ON)

include(FetchContent)

FetchContent_Declare(lua
  GIT_REPOSITORY     https://github.com/walterschell/Lua.git
  GIT_TAG            v5.4.5
)
FetchContent_MakeAvailable(lua)

FetchContent_Declare(sol2
  GIT_REPOSITORY     https://github.com/ThePhD/sol2.git
  GIT_TAG            v3.3.1
)
FetchContent_MakeAvailable(sol2)

# Add Library
file(GLOB_RECURSE heart_engine_sources CONFIGURE_DEPENDS src/*.cpp)
add_library(HeartEngine ${heart_engine_sources})

# Set defines.
if (USE_EDITOR)
    target_compile_definitions(HeartEngine PUBLIC EDITOR)
endif()

if (USE_DEBUG)
    target_compile_definitions(HeartEngine PUBLIC DEBUG)
endif()

target_compile_definitions(HeartEngine PUBLIC SOL_ALL_SAFETIES_ON=1)

target_include_directories(HeartEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/heart)
target_include_directories(HeartEngine PUBLIC ${sol2_SOURCE_DIR}/include)
target_include_directories(HeartEngine PUBLIC ${lua_SOURCE_DIR}/lua-5.4.5/include)

target_include_directories(sol2 INTERFACE $<BUILD_INTERFACE:${lua_SOURCE_DIR}/lua-5.4.5/include>)

target_link_libraries(HeartEngine lua_static)
target_link_libraries(HeartEngine sol2::sol2)

# Move/binary zip assets.
if (USE_EDITOR)
    add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../assets ${CMAKE_CURRENT_BINARY_DIR}/../assets
    )
    add_dependencies(HeartEngine copy_assets)
else()
    find_package(Python3 REQUIRED)

    add_custom_target(ResourcePackagerCommand ALL
      COMMAND Python3 ${CMAKE_CURRENT_SOURCE_DIR}/../tools/Resourcepackager.py
        ${CMAKE_CURRENT_BINARY_DIR}/../_deps/lua-build
        ${CMAKE_CURRENT_SOURCE_DIR}/../assets
        ${CMAKE_CURRENT_BINARY_DIR}/../data.heart
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/../_deps/lua-build/luac.exe
    )

    add_custom_command(
      TARGET HeartEngine POST_BUILD
      COMMAND ${ResourcePackagerCommand}
    )
endif()
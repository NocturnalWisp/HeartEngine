set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Os")

find_library(LuaEngine LuaEngine)
include_directories(${LuaEngine_SOURCE_DIR}/include)
link_libraries(LuaEngine)
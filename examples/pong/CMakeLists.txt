cmake_minimum_required(VERSION 3.5)
project(heart_ex_pong)

set(USE_EDITOR OFF)

include(../../tools/Main.cmake)

include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp)

# Heart Engine
target_link_libraries(${PROJECT_NAME} HertEngine)
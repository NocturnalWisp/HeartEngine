cmake_minimum_required(VERSION 3.5)
project(heart_physac VERSION 1.0.0)

add_library(heart_physac src/physac_core.cpp)
target_include_directories(heart_physac PUBLIC include)

# Grab physac and add it as an interface library.
FetchContent_Declare(physac
    GIT_REPOSITORY     https://github.com/victorfisac/Physac.git
    GIT_TAG            master
    CONFIGURE_COMMAND  ""
    BUILD_COMMAND      ""
)
FetchContent_GetProperties(physac)
if(NOT physac_POPULATED)
  FetchContent_Populate(physac)
endif()
add_library(physac INTERFACE)
target_include_directories(physac INTERFACE ${physac_SOURCE_DIR}/src)

# Attach raylib to the physac interface library.
FetchContent_Declare(raylib
    GIT_REPOSITORY     https://github.com/raysan5/raylib.git
    GIT_TAG            4.5.0
)
FetchContent_MakeAvailable(${name})
target_link_libraries(physac INTERFACE raylib)

# Also attach raylib to this module
target_include_directories(heart_physac PUBLIC ${raylib_SOURCE_DIR})
target_link_libraries(heart_physac PUBLIC raylib)
FetchLibraryGit(heart_physac raylib_cpp https://github.com/RobLoach/raylib-cpp.git v4.5.0)

# Include and link physac to module.
target_include_directories(heart_physac PUBLIC ${physac_SOURCE_DIR}/src)
target_link_libraries(heart_physac PUBLIC physac)

LinkLibrary(heart_physac HeartEngine core/include)
LinkLibrary(heart_physac heart_raylib_core include)
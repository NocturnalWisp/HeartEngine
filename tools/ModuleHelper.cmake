set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Os")

include(FetchContent)

function(LinkLibrary target name includeSubPath)
    find_library(${name} ${CMAKE_BINARY_DIR}/${name})
    if (NOT TARGET ${name})
        message(FATAL_ERROR "Library not found: ${name}. Did you forget to use LoadModule in your main CMakeLists.txt?")
    endif()
    target_include_directories(${target} PUBLIC ${${name}_SOURCE_DIR}/${includeSubPath})
    target_link_libraries(${target} PUBLIC ${name})
endfunction()

function(FetchLibraryGit target name repo tag)
    FetchContent_Declare(${name}
    GIT_REPOSITORY     ${repo}
    GIT_TAG            ${tag}
    )
    FetchContent_MakeAvailable(${name})
    target_include_directories(${target} PUBLIC ${${name}_SOURCE_DIR})
    target_link_libraries(${target} PUBLIC ${name})
endfunction()
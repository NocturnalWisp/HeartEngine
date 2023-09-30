set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Os")

include(FetchContent)

find_library(HeartEngine HeartEngine)
include_directories(${HeartEngine_SOURCE_DIR}/include)
link_libraries(HeartEngine)

function(FetchLibraryGit target name repo tag)
    FetchContent_Declare(${name}
    GIT_REPOSITORY     ${repo}
    GIT_TAG            ${tag}
    )
    FetchContent_MakeAvailable(${name})
    target_include_directories(${target} PUBLIC ${${name}_SOURCE_DIR})
    target_link_libraries(${target} PUBLIC ${name})
endfunction()
function(LoadModule target modulePath includeSubPath moduleName)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${modulePath})
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${modulePath}/${includeSubPath})
    target_link_libraries(${target} PUBLIC ${moduleName})
    # set(${moduleName}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${modulePath}/src)
    # set(${moduleName}_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${modulePath}/${includeSubPath})
endfunction()

# Heart Engine
# LoadModule(${PROJECT_NAME} core include HeartEngine)
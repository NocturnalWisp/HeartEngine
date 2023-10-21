function(LoadModule target modulePath includeSubPath moduleName)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${modulePath})
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${modulePath}/${includeSubPath})
    target_link_libraries(${target} PUBLIC ${moduleName})
endfunction()

# Heart Engine
# LoadModule(${PROJECT_NAME} core include HeartEngine)
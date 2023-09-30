function(load_module modulePath includePath moduleName)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${modulePath})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${includePath})
    link_libraries(${moduleName})
endfunction()

load_module(core core/include HeartEngine)
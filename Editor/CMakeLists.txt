file(GLOB_RECURSE CATALYST_EDITOR_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_executable(Catalyst_Editor ${CATALYST_EDITOR_SOURCES})

target_link_libraries(Catalyst_Editor
        PUBLIC Catalyst_Maths
        PUBLIC Catalyst
)

target_include_directories(Catalyst_Editor
        PUBLIC include
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(TARGET Catalyst_Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Catalyst>
        $<TARGET_FILE_DIR:Catalyst_Editor>
)

add_custom_command(TARGET Catalyst_Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/TestProject"
        "$<TARGET_FILE_DIR:Catalyst_Editor>/TestProject"
)

if(USE_OPENGL)

    add_custom_command(TARGET Catalyst_Editor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:CatalystOpenGL>
            $<TARGET_FILE_DIR:Catalyst_Editor>
    )

    target_compile_definitions(Catalyst_Editor PUBLIC USE_OPEN_GL)
    target_link_libraries(Catalyst_Editor
            PUBLIC CatalystOpenGL
    )

endif ()
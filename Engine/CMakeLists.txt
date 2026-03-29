add_subdirectory(Maths)
add_subdirectory(Core)

if(USE_OPENGL)
    add_subdirectory(OpenGLImpl)
endif ()
include(FetchContent)
include(GenerateExportHeader)

file(GLOB_RECURSE CATALYST_OPENGL_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8
        SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(glad)

add_library(CatalystOpenGL SHARED ${CATALYST_OPENGL_SOURCES})

generate_export_header(CatalystOpenGL
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/catalyst_opengl_export.h
)

glad_add_library(glad_gl STATIC REPRODUCIBLE API gl:core=4.6)

target_link_libraries(CatalystOpenGL
        PUBLIC Catalyst
        PUBLIC Catalyst_Maths
        PUBLIC glfw
        PUBLIC glad_gl
)

target_include_directories(CatalystOpenGL
        PUBLIC include
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
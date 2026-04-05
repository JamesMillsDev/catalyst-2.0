include(FetchContent)
include(GenerateExportHeader)

file(GLOB_RECURSE CATALYST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.4
)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SHARED_LIBS   OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS          OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
)
FetchContent_MakeAvailable(stb)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

add_library(Catalyst SHARED ${CATALYST_SOURCES})

generate_export_header(Catalyst
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/catalyst_export.h
)

target_link_libraries(Catalyst
        PUBLIC Catalyst_Maths
        PUBLIC assimp
        PRIVATE stb
)

target_include_directories(Catalyst
        PUBLIC include
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
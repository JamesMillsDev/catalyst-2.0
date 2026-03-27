file(GLOB_RECURSE CATALYST_MATHS_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

include(FetchContent)
add_library(Catalyst_Maths STATIC ${CATALYST_MATHS_SOURCES})

set_target_properties(Catalyst_Maths PROPERTIES
        OUTPUT_NAME "Catalyst.Maths"
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

target_link_libraries(Catalyst_Maths PUBLIC glm::glm)

target_include_directories(Catalyst_Maths
        PUBLIC include
)
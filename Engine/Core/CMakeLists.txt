file(GLOB_RECURSE CATALYST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(Catalyst SHARED ${CATALYST_SOURCES})

include(GenerateExportHeader)
generate_export_header(Catalyst
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/catalyst_export.h
)

target_link_libraries(Catalyst
        PUBLIC Catalyst_Maths
)

target_include_directories(Catalyst
        PUBLIC include
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
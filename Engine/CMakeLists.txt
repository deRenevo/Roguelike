add_library(Engine STATIC)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
)

file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp"
)

target_sources(Engine PRIVATE ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public
)

target_link_libraries(Engine PUBLIC raylib)

set_target_properties(Engine PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
)
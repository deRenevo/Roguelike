file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
)

file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp"
)

add_executable(Game main.cpp)

target_sources(Game PRIVATE
        ${GAME_SOURCES}
        ${GAME_HEADERS}
)

target_include_directories(Game PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public
        ${CMAKE_SOURCE_DIR}/Engine/Source/Public
)

target_link_libraries(Game PRIVATE
        Engine
        raylib
)

set_target_properties(Game PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
)

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Game>/Assets"
)
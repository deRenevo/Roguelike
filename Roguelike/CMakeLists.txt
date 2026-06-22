# CMakeList.txt: проект CMake для Roguelike; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Roguelike 
"main.cpp"
"Roguelike.h" "Roguelike.cpp" 
"Public/Utility/Draw/DrawUtility.h" "Private/Utility/Draw/DrawUtility.cpp" 
"Public/UI/Menu.h" "Private/UI/Menu.cpp"
"Public/Input/InputMenu.h" "Private/Input/InputMenu.cpp"
"Public/UI/Widgets/Button.h" "Private/UI/Widgets/Button.cpp")

target_include_directories(Roguelike PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Roguelike PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.14)
  set_property(TARGET Roguelike PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

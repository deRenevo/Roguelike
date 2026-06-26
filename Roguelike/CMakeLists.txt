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
 "Public/Core/Scene/SceneManager.h" "Private/Core/Scene/SceneManager.cpp" 
 "Public/Core/Scene/Scene.h" "Private/Core/Scene/Scene.cpp" 
 "Public/Core/Scene/SceneFactory.h" "Private/Core/Scene/SceneFactory.cpp" 
 "Private/Core/HUD/HUD.cpp" "Public/Core/HUD/HUD.h" 
 "Public/Scene/MenuScene.h" "Private/Scene/MenuScene.cpp"
 "Public/Core/Utility/Draw/DrawUtility.h" "Private/Core/Utility/Draw/DrawUtility.cpp" 
 "Public/Core/HUD/HUDFactory.h" "Private/Core/HUD/HUDFactory.cpp"
 "Public/HUD/DebugHUD.h" "Private/HUD/DebugHUD.cpp" 
 "Public/Core/Widgets/WidgetsElements/Button.h" "Private/Core/Widgets/WidgetsElements/Button.cpp" 
 "Public/Core/Widgets/WidgetsElements/Widget.h" "Private/Core/Widgets/WidgetsElements/Widget.cpp" "Public/Core/Widgets/WidgetsElements/Container.h" "Private/Core/Widgets/WidgetsElements/Container.cpp" "Public/Core/Utility/Struct.h" "Private/Core/Utility/Struct.cpp" "Public/Core/Widgets/WidgetsElements/CanvasPanel.h" "Private/Core/Widgets/WidgetsElements/CanvasPanel.cpp" "Public/HUD/MenuHUD.h" "Private/HUD/MenuHUD.cpp")

target_include_directories(Roguelike PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Roguelike PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.14)
  set_property(TARGET Roguelike PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

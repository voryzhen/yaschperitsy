add_library (

    yaschperitsy_core

    STATIC

    App.cpp
    Window.cpp
    Logger.cpp

    scene/Layer.cpp
    scene/LayerStack.cpp
    scene/Scene.cpp

    resource_manager/ResourceManager.cpp

    renderer/Renderer.cpp

    input/Input.cpp

)

find_package ( spdlog REQUIRED )

find_package ( SDL2       REQUIRED CONFIG )
find_package ( SDL2_image REQUIRED CONFIG )
find_package ( SDL2_ttf   REQUIRED CONFIG )

target_include_directories ( yaschperitsy_core PRIVATE ${CMAKE_SOURCE_DIR}/src )

target_link_libraries (

    yaschperitsy_core

    spdlog::spdlog

    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf

)

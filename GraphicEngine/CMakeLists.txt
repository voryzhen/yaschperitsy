project ( GraphicEngine )

add_library ( GraphicEngine

    GraphicEngine.cpp
    GraphicSystem.cpp
    Renderer.cpp
    RendererImpl/RendererImpl.cpp
    ResourceManager/ResourceManager.cpp
    ResourceManager/ResourceStorage.cpp
    Input/Input.cpp

)

find_package ( SDL2       REQUIRED CONFIG )
find_package ( SDL2_image REQUIRED CONFIG )
find_package ( SDL2_ttf   REQUIRED CONFIG )

target_include_directories ( GraphicEngine PRIVATE

    ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS}
    
    ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries      ( GraphicEngine PRIVATE ${SDL2_LIBRARIES}    ${SDL2_image_LIBRARIES}    ${SDL2_ttf_LIBRARIES} )

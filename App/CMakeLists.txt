project ( GameEngine )

add_library ( GameEngine

    App.cpp
    Scene/Scene.cpp
    Scene/SceneManager.cpp

)

target_include_directories ( GameEngine PRIVATE

    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}

)

target_link_libraries ( GameEngine PRIVATE 

    GraphicEngine
    ECS

)

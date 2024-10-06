project ( Yaschperitsy )

add_executable ( Yaschperitsy

    GameSanbox.cpp
    Game.cpp

    Scenes/GameScene/GameScene.cpp
    Scenes/GameScene/YaschperitsyController.cpp
    Scenes/MainMenuScene/MainMenuScene.cpp
    Scenes/GameEndScene/GameEndScene.cpp

)

target_include_directories ( Yaschperitsy PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_libraries ( Yaschperitsy PRIVATE GameEngine )

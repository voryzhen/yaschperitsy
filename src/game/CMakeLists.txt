project( game )

set (

    SOURCE

    game/layers/MainMenuLayer.cpp
    game/layers/PauseMenuLayer.cpp
    game/layers/SettingsMenuLayer.cpp
    game/layers/BackgroundLayer.cpp
    game/layers/GameEndLayer.cpp

    game/scenes/GameScene.cpp
    game/scenes/YaschperitsyController.cpp

    game/button/Button.cpp
    game/label/Label.cpp

    game/Game.cpp
    game/Assets.cpp

    main.cpp

)

add_executable ( game ${SOURCE} )

find_library ( yaschperitsy_core
    HINTS "${CMAKE_SOURCE_DIR}/"
)

target_include_directories ( game PRIVATE ${CMAKE_SOURCE_DIR}/src )

target_link_libraries (

    game

    yaschperitsy_core

)

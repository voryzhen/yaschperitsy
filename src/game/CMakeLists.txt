project( game )

set (

    SOURCE

    game/main_menu/MainMenu.cpp
    game/main_menu/SettingsMenu.cpp
    game/main_menu/EntityLayer.cpp

    game/button/Button.cpp

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

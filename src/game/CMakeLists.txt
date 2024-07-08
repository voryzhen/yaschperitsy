project( game )

set (

    SOURCE

    game/Game.cpp
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

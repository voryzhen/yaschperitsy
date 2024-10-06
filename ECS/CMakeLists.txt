project ( ECS )

add_library ( ECS

    Entity.cpp
    Manager.cpp
    TypesID.cpp

)

target_include_directories (

    ECS

    PRIVATE

    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}

)

target_link_libraries ( ECS PRIVATE GraphicEngine )

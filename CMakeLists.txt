cmake_minimum_required ( VERSION 3.29.2 )

project ( yaschperitsy )

# find_package ( SDL2 REQUIRED )

include_directories ( include /opt/homebrew/include/SDL2 ${SDL2_INCLUDE_DIRS} )
link_directories ( /opt/homebrew/lib ${SDL2_LIB_DIRS} )

set (CMAKE_CXX_STANDARD 17)

add_executable ( yaschperitsy 

  src/app.cpp
  src/keyboard_controller.cpp
  src/entity.cpp
  src/game.cpp
  src/main.cpp
  src/resource_manager.cpp
  src/topbar.cpp

)

target_link_libraries ( yaschperitsy SDL2 SDL2_image SDL2_ttf ${SDL2_LIBRARIES} )

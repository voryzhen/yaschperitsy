cmake_minimum_required ( VERSION 3.29.3 )

# set ( CMAKE_C_COMPILER   "/opt/homebrew/opt/llvm/bin/clang" )
# set ( CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

# set ( CMAKE_CXX_FLAGS "-Wall" )

set ( SOURCE

  src/main.cpp
  src/app/app.cpp
  src/app/window.cpp
  src/app/resource_manager.cpp

  src/game/game.cpp
  src/game/topbar.cpp

  src/ecs/game_fabric.cpp

  src/ui/base_screen.cpp
  src/ui/screen_manager.cpp
  src/ui/screens.cpp
  src/ui/button.cpp

)

project ( yaschperitsy )

find_package ( SDL2       REQUIRED CONFIG )
find_package ( SDL2_image REQUIRED CONFIG )
find_package ( SDL2_ttf   REQUIRED CONFIG )

add_executable ( yaschperitsy ${SOURCE} )

target_include_directories ( yaschperitsy PRIVATE ${SDL2_INCLUDE_DIRS} src )

target_link_directories    ( yaschperitsy PRIVATE ${SDL2_LIB_DIRS} )

target_link_libraries ( 

  yaschperitsy PRIVATE
  
  SDL2::SDL2main
  SDL2::SDL2
  SDL2_image::SDL2_image
  sdl_ttf::sdl_ttf

)

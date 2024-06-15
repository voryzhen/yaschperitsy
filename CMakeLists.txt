cmake_minimum_required ( VERSION 3.29.3 )

# set ( CMAKE_C_COMPILER   "/opt/homebrew/opt/llvm/bin/clang" )
# set ( CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_FLAGS "-Wall -g" )

project ( yaschperitsy )

include_directories ( 

  include
  /opt/homebrew/include/SDL2
  ${SDL2_INCLUDE_DIRS}

)

link_directories (

  /opt/homebrew/lib
  ${SDL2_LIB_DIRS}

)

add_executable ( yaschperitsy

  src/main.cpp
  src/app.cpp
  src/window.cpp
  src/resource_manager.cpp

  src/game/game.cpp
  src/game/topbar.cpp
  src/game/vector2D.cpp
  src/ui/base_screen.cpp
  src/ui/screen_manager.cpp
  src/ui/screens.cpp
  src/ui/button.cpp

)

target_link_libraries ( yaschperitsy 

  SDL2
  SDL2_image
  SDL2_ttf
  ${SDL2_LIBRARIES}

)

# tests

if ( APPLE )

project ( yaschperitsy_test )

find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED )

include_directories ( ${Boost_INCLUDE_DIR} )
link_directories ( ${Boost_LIBRARY_DIR} )

add_executable( yaschperitsy_test

  tests/test_vector2D.cpp
  src/game/vector2D.cpp

)

target_link_libraries( yaschperitsy_test

  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}

)

endif()

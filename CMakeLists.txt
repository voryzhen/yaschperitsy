cmake_minimum_required ( VERSION 3.29.3 )

# set ( CMAKE_C_COMPILER   "/opt/homebrew/opt/llvm/bin/clang" )
# set ( CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

# set ( CMAKE_CXX_FLAGS "-Wall" )

set ( SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} src )

if ( APPLE )

set ( SDL2_LIBRARIES SDL2 SDL2_image SDL2_ttf )
set ( SDL2_LIB_DIRS "/opt/homebrew/lib" )
set ( SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} /opt/homebrew/include/SDL2 )

endif()

project ( yaschperitsy )

set ( SOURCE

  src/main.cpp
  src/app/app.cpp
  src/app/window.cpp
  src/app/resource_manager.cpp

  src/game/game.cpp
  src/game/topbar.cpp

  src/ui/base_screen.cpp
  src/ui/screen_manager.cpp
  src/ui/screens.cpp
  src/ui/button.cpp

)

add_executable             ( yaschperitsy         ${SOURCE} )
target_include_directories ( yaschperitsy PRIVATE ${SDL2_INCLUDE_DIRS} )
target_link_directories    ( yaschperitsy PRIVATE ${SDL2_LIB_DIRS} )
target_link_libraries      ( yaschperitsy         ${SDL2_LIBRARIES} )

# tests

if ( APPLE )

project ( yaschperitsy_test )

find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED )

include_directories ( ${Boost_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} /opt/homebrew/include/SDL2 )
link_directories ( ${Boost_LIBRARY_DIR} ${SDL2_LIB_DIRS} /opt/homebrew/lib )

add_executable( yaschperitsy_test

  tests/test_vector2D.cpp
  tests/test_ecs_icomponent.cpp
  tests/test_ecs_components.cpp
  tests/test_ecs_manager.cpp
  tests/test_ecs_entity.cpp

)

target_link_libraries( yaschperitsy_test

  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${SDL2_LIBRARIES}
  SDL2
  SDL2_image
  SDL2_ttf

)

endif()

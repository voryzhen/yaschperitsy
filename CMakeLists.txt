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

  src/ui/base_screen.cpp
  src/ui/screen_manager.cpp
  src/ui/screens.cpp
  src/ui/button.cpp

)

if ( APPLE )

  # find_package ( SDL2 REQUIRED )

  set ( SDL2_LIBRARIES SDL2 SDL2_image SDL2_ttf )
  set ( SDL2_LIB_DIRS "/opt/homebrew/lib" )
  set ( SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} /opt/homebrew/include/SDL2 )

endif()

set ( INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} src )
set ( LIB_DIRS     ${SDL2_LIB_DIRS} )
set ( LIBRARIES    ${SDL2_LIBRARIES} )

project ( yaschperitsy )

add_executable             ( yaschperitsy         ${SOURCE} )
target_include_directories ( yaschperitsy PRIVATE ${INCLUDE_DIRS} )
target_link_directories    ( yaschperitsy PRIVATE ${LIB_DIRS} )
target_link_libraries      ( yaschperitsy         ${LIBRARIES} )

# tests

if ( APPLE )

project ( yaschperitsy_test )

find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED )

include_directories ( ${Boost_INCLUDE_DIR} ${INCLUDE_DIRS} )
link_directories ( ${Boost_LIBRARY_DIR} ${LIB_DIRS} )

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
  ${LIBRARIES}

)

endif()

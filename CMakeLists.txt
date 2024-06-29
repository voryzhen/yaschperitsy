cmake_minimum_required ( VERSION 3.29.3 )

# set ( CMAKE_C_COMPILER   "/opt/homebrew/opt/llvm/bin/clang" )
# set ( CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( CMAKE_CXX_FLAGS "-Wall -g" )

set ( SOURCE

  src/main.cpp
  src/core/App.cpp
  src/core/Window.cpp
  src/core/ResourceManager.cpp
  src/core/Logger.cpp
  src/core/LayerStack.cpp

  src/old_game/OldGame.cpp
  src/old_game/Topbar.cpp

  src/game/UILayer.cpp
  src/game/Game.cpp

  src/core/ecs/EntityCreator.cpp

  src/ui/BaseScreen.cpp
  src/ui/ScreenManager.cpp
  src/ui/Button.cpp

  src/ui/screens/StartScreen.cpp
  src/ui/screens/SettingsScreen.cpp
  src/ui/screens/GameScreen.cpp
  src/ui/screens/GameEndScreen.cpp

)

project ( yaschperitsy )

find_package ( SDL2       REQUIRED CONFIG )
find_package ( SDL2_image REQUIRED CONFIG )
find_package ( SDL2_ttf   REQUIRED CONFIG )

find_package ( spdlog REQUIRED )

add_executable ( yaschperitsy ${SOURCE} )

target_include_directories ( yaschperitsy PRIVATE ${SDL2_INCLUDE_DIRS} src )

target_link_directories    ( yaschperitsy PRIVATE ${SDL2_LIB_DIRS} )

target_link_libraries ( 

  yaschperitsy PRIVATE
  
  SDL2::SDL2main
  SDL2::SDL2
  SDL2_image::SDL2_image
  sdl_ttf::sdl_ttf

  spdlog::spdlog

)

# ----------

if ( APPLE )

  project ( yaschperitsy_test )

  # set ( CMAKE_BUILD_TYPE "Debug" )

  find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED )

  add_executable( yaschperitsy_test

    tests/test_vector2D.cpp
    tests/test_ecs_icomponent.cpp
    tests/test_ecs_components.cpp
    tests/test_ecs_manager.cpp
    tests/test_ecs_entity.cpp
    tests/test_entity_creator.cpp

    src/core/ecs/EntityCreator.cpp

    tests/events_system/app_events.cpp
    tests/events_system/mouse_events.cpp
    tests/events_system/keyboard_events.cpp

    tests/events_system/event_dispatcher.cpp

    )

  target_include_directories ( yaschperitsy_test PRIVATE ${Boost_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} src )
  target_link_directories    ( yaschperitsy_test PRIVATE ${Boost_LIBRARY_DIR} ${SDL2_LIB_DIRS} )
  

  target_link_libraries( yaschperitsy_test

    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}

    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf

  )

  endif()

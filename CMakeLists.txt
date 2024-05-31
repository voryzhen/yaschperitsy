# main project

cmake_minimum_required ( VERSION 3.29.2 )

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

set ( CMAKE_CXX_STANDARD    17      )
set ( CMAKE_CXX_FLAGS       "-Wall" )
set ( CMAKE_CXX_FLAGS_DEBUG "-g"    )
set ( CMAKE_BUILD_TYPE      Debug   )

add_executable ( yaschperitsy

  src/app.cpp
  src/game.cpp
  src/main.cpp
  src/resource_manager.cpp
  src/topbar.cpp
  src/utility.cpp
  src/vector2D.cpp

)

target_link_libraries ( yaschperitsy 

  SDL2
  SDL2_image
  SDL2_ttf
  ${SDL2_LIBRARIES}

)


#-----
# tests

project ( yaschperitsy_test )

find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
link_directories(${Boost_LIBRARY_DIR})
# include_directories ( 

#   include
#   /opt/homebrew/include

# )

# link_directories (

#   /opt/homebrew/lib
#   /opt/homebrew/Cellar/boost/1.85.0/lib

# )

add_executable( yaschperitsy_test

  tests/test_vector2D.cpp
  src/vector2D.cpp

)

# target_link_libraries(yaschperitsy_test boost_unit_test_framework)

target_link_libraries( yaschperitsy_test
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)


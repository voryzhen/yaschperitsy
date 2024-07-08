project( events.tests )

find_package( Boost COMPONENTS system filesystem unit_test_framework REQUIRED )

set (

    SOURCE

    events.tests/AppEvents.cpp
    events.tests/MouseEvents.cpp
    events.tests/KeyboardEvents.cpp
    events.tests/EventDispatcher.cpp

)

add_executable ( events.tests ${SOURCE} )

target_include_directories ( events.tests PRIVATE ${CMAKE_SOURCE_DIR}/src )

target_link_libraries(

    events.tests

    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}

)

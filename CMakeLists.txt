cmake_minimum_required ( VERSION 3.30.3 )

project ( yaschperitsy )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# set ( CMAKE_CXX_FLAGS "-Wall -g" )

add_subdirectory ( IOSystem )
add_subdirectory ( App )
add_subdirectory ( ECS )
add_subdirectory ( Yaschperitsy )

# clang++ -O1 -g -fsanitize=address  main.cpp
# ASAN_OPTIONS=detect_leaks=1 ./a.out

cmake_minimum_required ( VERSION 3.30.0 )

# set ( CMAKE_C_COMPILER   "/opt/homebrew/opt/llvm/bin/clang" )
# set ( CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" )

set ( CMAKE_CXX_STANDARD 23 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( CMAKE_CXX_FLAGS "-Wall -g" )

project( yaschperitsy )

add_subdirectory( src )

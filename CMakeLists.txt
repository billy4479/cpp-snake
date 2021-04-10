cmake_minimum_required(VERSION 3.10)

project(snake)

file( GLOB HEADERS src/*.hpp )
file( GLOB SOURCES src/*.cpp )

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable( snake ${HEADERS} ${SOURCES} )
target_link_libraries( snake ${CURSES_LIBRARIES} )

target_compile_features(snake PRIVATE cxx_std_17)
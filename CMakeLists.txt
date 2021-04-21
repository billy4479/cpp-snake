cmake_minimum_required(VERSION 3.10)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file( GLOB SOURCES src/*.cpp )

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable( snake ${HEADERS} ${SOURCES} )
target_link_libraries( snake ${CURSES_LIBRARIES} )
cmake_minimum_required(VERSION 3.10.2)

project(ncstock)

include_directories(include)

file(GLOB srcs src/*.cpp)

add_executable(ncstock src/main.cpp)

target_link_libraries(ncstock PRIVATE ncurses)

target_sources(
    ncstock PRIVATE
    ${srcs}
)
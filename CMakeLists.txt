cmake_minimum_required(VERSION 3.10.2)

project(ncstock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lncursesw -lPocoNet")

include_directories(include)

file(GLOB srcs src/*.cpp)

add_executable(ncstock src/main.cpp)

target_link_libraries(ncstock PRIVATE ncursesw PocoNet)

target_sources(
    ncstock PRIVATE
    ${srcs}
)
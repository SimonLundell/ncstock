cmake_minimum_required(VERSION 3.20)

project(ncstock)

add_compile_options(-g -Wall)

find_library(mycurs ncurses REQUIRED)
if (${mycurs} STREQUAL mycurs-NOTFOUND)
    message(FATAL ERROR "Shits broke")
else()
    message(STATUS "Found ${mycurs}")
endif()

find_library(mypoconet PocoNet REQUIRED)
if (${mypoconet} STREQUAL mypoconet-NOTFOUND)
    message(FATAL ERROR "Shits broke")
else()
    message(STATUS "Found ${mypoconet}")
endif()

find_library(mypocofoundation PocoFoundation REQUIRED)
if (${mypocofoundation} STREQUAL mypocofoundation-NOTFOUND)
    message(FATAL ERROR "Shits broke")
else()
    message(STATUS "Found ${mypocofoundation}")
endif()

find_library(mypoconetssl PocoNetSSL REQUIRED)
if (${mypoconetssl} STREQUAL mypoconetssl-NOTFOUND)
    message(FATAL ERROR "Shits broke")
else()
    message(STATUS "Found ${mypoconetssl}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lncurses -lPocoNet -lPocoFoundation -lPocoNetSSL -pthread")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB srcs src/*.cpp)

add_executable(ncstock ${srcs})

target_link_libraries(ncstock PRIVATE ncurses PocoNet PocoFoundation PocoNetSSL)

target_sources(
    ncstock PRIVATE
    ${srcs}
)

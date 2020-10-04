cmake_minimum_required(VERSION 3.13)
project(dvb)

set(CMAKE_CXX_STANDARD 17)

set(DVB_ROOT ${CMAKE_SOURCE_DIR})

add_executable(dvb source/main.cpp)

# third_party
add_subdirectory(third_party/drogon)
target_link_libraries(dvb PRIVATE drogon)
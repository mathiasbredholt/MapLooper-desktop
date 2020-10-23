cmake_minimum_required(VERSION 3.17)
project(MapLooper-desktop VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

include(link/AbletonLinkConfig.cmake)

find_library(LIBMAPPER mapper)
include_directories(/usr/local/include)
include_directories(MapLooper/include)
add_executable(MapLooper-desktop MapLooper-desktop.cpp)
target_link_libraries(MapLooper-desktop ${LIBMAPPER})
target_link_libraries(MapLooper-desktop Ableton::Link)

cmake_minimum_required(VERSION 3.17)
project(MapLooper-test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

include(link/AbletonLinkConfig.cmake)

find_library(LIBMAPPER mapper)
include_directories(MapLooper/include)
add_executable(test test.cpp)
target_link_libraries(test ${LIBMAPPER})
target_link_libraries(test Ableton::Link)


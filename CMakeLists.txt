cmake_minimum_required(VERSION 3.17)
project(MapLooper-test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(MapLooper-test MapLooper-test.cpp)
find_library(LIBMAPPER mapper)
target_link_libraries(MapLooper-test ${LIBMAPPER})

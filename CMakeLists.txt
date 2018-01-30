cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(PeakFinder)

include_directories(include)

add_library(PeakFinder SHARED PeakFinder.h PeakFinder.cpp)

set_target_properties(PeakFinder PROPERTIES SUFFIX .so)

file(COPY TestScript        DESTINATION .)
file(COPY PeakFinder.cpp    DESTINATION .)
file(COPY PeakFinder.h      DESTINATION .)
cmake_minimum_required(VERSION 3.23)
project(orbslam3_FAST_BRIEF)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4.2 REQUIRED)
MESSAGE("OPENCV VERSION:")
MESSAGE(${OpenCV_VERSION})

include_directories(..)
include_directories(utils)

add_executable(orbslam3_FAST_BRIEF
        main.cpp
        ORBextractor.cc)

target_link_libraries(orbslam3_FAST_BRIEF ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.17)
project(Soundsolved)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}lib/)

set(target_sources
        Soundsolved.cpp
        SVAudioDevices.cpp)
set(target_includes
        Soundsolved.h
        SVHelper.h
        SVAudioDevices.h
        SVVolumeControl.h)

list(TRANSFORM target_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/)
list(TRANSFORM target_includes PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(Soundsolved ${target_sources} ${target_includes})
add_executable(test ${target_sources} main.cpp)

include_directories(PUBLIC include)
cmake_minimum_required(VERSION 3.17)
project(Soundsolved)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}lib/)

set(devices_includes
        SVHeadphone.h
        SVMicrophone.h
        SVSpeaker.h)

set(devices_sources
        SVHeadphone.cpp
        SVMicrophone.cpp
        SVSpeaker.cpp)

list(TRANSFORM devices_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/devices/)
list(TRANSFORM devices_includes PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/include/devices/)

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

add_library(Soundsolved ${target_sources} ${target_includes}
        ${devices_sources} ${devices_includes})

add_executable(test ${target_sources}
                    ${devices_sources}
                    main.cpp)

include_directories(PUBLIC include include/devices)
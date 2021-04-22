cmake_minimum_required(VERSION 3.0)
project(tv-native-apis C CXX)

add_subdirectory(appswitching-control-block)
add_subdirectory(dile-libs)
add_subdirectory(lgncapi)
add_subdirectory(libndl)
add_subdirectory(starfish-media-pipeline)
add_subdirectory(webos-helpers)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(samples)
endif()
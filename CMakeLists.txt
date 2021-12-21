cmake_minimum_required(VERSION 3.0)
project(tv-native-apis C CXX)

option(BUILD_DOCS "Build API references" OFF)

add_subdirectory(appswitching-control-block)
add_subdirectory(dile-libs)
add_subdirectory(libndl-media)
add_subdirectory(starfish-media-pipeline)
add_subdirectory(webos-helpers)
add_subdirectory(libim)
add_subdirectory(libvt)
add_subdirectory(libgm)
add_subdirectory(libvtcapture)
add_subdirectory(libgm-wayland)
add_subdirectory(libhalgal)
add_subdirectory(lgncapi)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(samples)
endif()

if (BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    add_custom_target(docs
            COMMAND ${CMAKE_COMMAND} -E env "DOXYGEN_OUTPUT_DIRECTORY=${CMAKE_BINARY_DIR}/docs" ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            VERBATIM)
endif()
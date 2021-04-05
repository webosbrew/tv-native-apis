find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

add_library(playerAPIs SHARED "src/StarfishMediaAPIs_stub.cpp")

set_target_properties(playerAPIs PROPERTIES SOVERSION 1)
target_include_directories(playerAPIs SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(playerAPIs SYSTEM PRIVATE ${GLIB_INCLUDE_DIRS})
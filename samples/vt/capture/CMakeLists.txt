find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(GLES REQUIRED IMPORTED_TARGET glesv2)

add_executable(sample-vt-capture capture.c)
set_target_properties(sample-vt-capture PROPERTIES OUTPUT_NAME capture)
target_link_libraries(sample-vt-capture vt PkgConfig::SDL2 PkgConfig::GLES)
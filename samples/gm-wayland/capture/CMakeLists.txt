find_package(PkgConfig REQUIRED)

pkg_check_modules(JPEG REQUIRED IMPORTED_TARGET libjpeg)

add_executable(sample-gmw-capture capture.c)
set_target_properties(sample-gmw-capture PROPERTIES OUTPUT_NAME gmw-capture)
target_link_libraries(sample-gmw-capture gm-wayland PkgConfig::JPEG)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JPEG REQUIRED IMPORTED_TARGET libjpeg)

add_executable(sample-dile-vt-capture dilecapture.c)
set_target_properties(sample-dile-vt-capture PROPERTIES OUTPUT_NAME dile-vt-capture)
target_link_libraries(sample-dile-vt-capture dile_vt PkgConfig::JPEG)

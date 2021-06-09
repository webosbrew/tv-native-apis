find_package(PkgConfig REQUIRED)

pkg_check_modules(JPEG REQUIRED IMPORTED_TARGET libjpeg)

add_executable(sample-vtcapture-capture capture.c)
set_target_properties(sample-vtcapture-capture PROPERTIES OUTPUT_NAME vtcapture-capture)
target_link_libraries(sample-vtcapture-capture vtcapture PkgConfig::JPEG)

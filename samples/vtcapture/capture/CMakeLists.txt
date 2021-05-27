find_package(PkgConfig REQUIRED)

add_executable(sample-vtcapture-capture capture.c)
set_target_properties(sample-vtcapture-capture PROPERTIES OUTPUT_NAME vtcapture-capture)
target_link_libraries(sample-vtcapture-capture vtcapture)

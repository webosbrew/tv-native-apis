find_package(PkgConfig REQUIRED)

add_executable(sample-halgal-capture capture.c)
set_target_properties(sample-halgal-capture PROPERTIES OUTPUT_NAME halgal-captureWithoutVideo)
target_link_libraries(sample-halgal-capture halgal)

add_executable(sample-halgal-captureWithVideo capture_withVideo.c)
set_target_properties(sample-halgal-captureWithVideo PROPERTIES OUTPUT_NAME halgal-capture)
target_link_libraries(sample-halgal-captureWithVideo halgal vtcapture)

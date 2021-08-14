find_package(PkgConfig REQUIRED)

add_executable(sample-halgal-capture capture.c)
set_target_properties(sample-halgal-capture PROPERTIES OUTPUT_NAME halgal-capture)
target_link_libraries(sample-halgal-capture halgal)

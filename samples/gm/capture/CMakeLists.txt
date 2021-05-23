find_package(PkgConfig REQUIRED)

add_executable(sample-gm-capture capture.c)
set_target_properties(sample-gm-capture PROPERTIES OUTPUT_NAME gm-capture)
target_link_libraries(sample-gm-capture gm)

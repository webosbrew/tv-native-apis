find_package(PkgConfig REQUIRED)
pkg_check_modules(PMLOG REQUIRED PmLogLib)

add_library(dile_vdec_direct SHARED src/dile_vdec_direct.c)
set_target_properties(dile_vdec_direct PROPERTIES SOVERSION 1)
target_include_directories(dile_vdec_direct PUBLIC include)

add_library(dile_audio_direct SHARED src/dile_audio_direct.c)
set_target_properties(dile_audio_direct PROPERTIES SOVERSION 1)
target_include_directories(dile_audio_direct PUBLIC include)

add_library(dile_vt SHARED src/dile_vt.c)
set_target_properties(dile_vt PROPERTIES SOVERSION 0)
target_include_directories(dile_vt PUBLIC include)
target_link_libraries(dile_vt PRIVATE ${PMLOG_LIBRARIES})

add_library(dile_boardinfo SHARED src/dile_boardinfo.c)
set_target_properties(dile_boardinfo PROPERTIES SOVERSION 1)
target_include_directories(dile_boardinfo PUBLIC include)
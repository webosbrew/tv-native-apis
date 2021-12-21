add_library(lgncopenapi SHARED
        src/lgnc_directaudio.c
        src/lgnc_directvideo.c
        src/lgnc_egl.c
        src/lgnc_gamepad.c
        src/lgnc_system.c
        include/_doc_modules.h
        )
set_target_properties(lgncopenapi PROPERTIES SOVERSION 2)
target_include_directories(lgncopenapi PUBLIC include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PMLOG REQUIRED PmLogLib)
pkg_check_modules(JSON REQUIRED json-c)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(LUNA_SERVICE REQUIRED luna-service2)

add_library(cgl SHARED
        src/cgl.c
        include/_doc_modules.h
        )
set_target_properties(cgl PROPERTIES SOVERSION 2)
target_include_directories(cgl PUBLIC include PRIVATE SYSTEM ${GLIB_INCLUDE_DIRS})
target_link_libraries(cgl PRIVATE gcc_s pthread AcbAPI dile_boardinfo dile_audio_direct dile_vdec_direct
        resource_mgr_client_c ${PMLOG_LIBRARIES} ${JSON_LIBRARIES} ${GLIB_LIBRARIES} ${LUNA_SERVICE_LIBRARIES})
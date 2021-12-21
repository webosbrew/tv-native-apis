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

add_library(cgl SHARED
        src/cgl.c
        include/_doc_modules.h
        )
set_target_properties(cgl PROPERTIES SOVERSION 2)
target_include_directories(cgl PUBLIC include)
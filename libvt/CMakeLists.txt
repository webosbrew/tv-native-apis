add_library(vt SHARED src/vt_openapi.c)
set_target_properties(vt PROPERTIES SOVERSION 1)
target_include_directories(vt PUBLIC include)
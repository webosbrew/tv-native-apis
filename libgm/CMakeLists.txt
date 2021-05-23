add_library(gm SHARED src/gm.c)
set_target_properties(gm PROPERTIES SOVERSION 1)
target_include_directories(gm PUBLIC include)

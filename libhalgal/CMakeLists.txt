add_library(halgal SHARED src/halgal.c)
set_target_properties(halgal PROPERTIES SOVERSION 1)
target_include_directories(halgal PUBLIC include)

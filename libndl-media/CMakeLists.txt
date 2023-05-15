add_library(NDL_directmedia SHARED src/NDL_directmedia_v1.c src/NDL_directmedia_v2.c)
set_target_properties(NDL_directmedia PROPERTIES SOVERSION 1)
target_include_directories(NDL_directmedia PUBLIC include)

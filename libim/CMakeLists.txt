add_library(im SHARED src/im.c)
set_target_properties(im PROPERTIES SOVERSION 1)
target_include_directories(im PUBLIC include)
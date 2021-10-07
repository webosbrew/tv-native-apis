add_library(gm-wayland SHARED src/gmw_c.c)
set_target_properties(gm-wayland PROPERTIES SOVERSION 1)
target_include_directories(gm-wayland PUBLIC include)

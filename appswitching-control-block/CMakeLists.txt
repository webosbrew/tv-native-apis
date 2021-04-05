add_library(AcbAPI SHARED src/AcbAPI.c)
set_target_properties(AcbAPI PROPERTIES SOVERSION 1)
target_include_directories(AcbAPI PUBLIC include)
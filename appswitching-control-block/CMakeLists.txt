add_library(AcbAPI SHARED src/AcbAPI.c)
set_target_properties(AcbAPI PROPERTIES SOVERSION 1)
target_include_directories(AcbAPI PUBLIC include)

add_library(Acb SHARED src/Acb.cpp)
set_target_properties(Acb PROPERTIES SOVERSION 1)
target_include_directories(Acb PUBLIC include)
add_library(vtcapture SHARED src/vtCaptureApi_c.c)
set_target_properties(vtcapture PROPERTIES SOVERSION 1)
target_include_directories(vtcapture PUBLIC include)

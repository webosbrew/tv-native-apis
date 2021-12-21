add_library(halgal SHARED src/halgal.c)
target_include_directories(halgal PUBLIC include)

# NOTE: This library is shipped in versions 0, 1 and 2, though all the symbols
# we use are cross-compatible betwen these versions.
# set_target_properties(halgal PROPERTIES SOVERSION 1)

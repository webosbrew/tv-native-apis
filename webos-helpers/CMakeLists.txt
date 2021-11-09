find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(LUNA_SERVICE REQUIRED luna-service2)

add_library(helpers SHARED src/libhelpers.c)
set_target_properties(helpers PROPERTIES SOVERSION 2)

target_include_directories(helpers PUBLIC include PRIVATE ${GLIB_INCLUDE_DIRS} ${LUNA_SERVICE_INCLUDE_DIRS})
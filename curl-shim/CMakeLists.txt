add_library(curl-shim SHARED shim.c easy.c slist.c)
target_link_libraries(curl-shim dl)

find_package(PkgConfig REQUIRED)

pkg_check_modules(CURL_SYS REQUIRED libcurl)

target_include_directories(curl-shim SYSTEM PUBLIC ${CURL_SYS_INCLUDE_DIRS})

install(TARGETS curl-shim LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
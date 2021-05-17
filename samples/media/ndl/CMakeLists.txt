include(BuildSample)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

set(WEBOS_APPID org.webosbrew.sample.ndl-webos4)
set(WEBOS_APPTITLE "NDL Sample")

add_executable(sample-ndl-webos4 main.c)
target_link_libraries(sample-ndl-webos4 PRIVATE PkgConfig::SDL2 NDL_directmedia esplayer-datasrc)
target_compile_definitions(sample-ndl-webos4 PRIVATE APPID="${WEBOS_APPID}")

common_build_ipk(sample-ndl-webos4)
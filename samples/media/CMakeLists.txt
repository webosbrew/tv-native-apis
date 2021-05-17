set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(WEBOS_APPICON ${CMAKE_CURRENT_SOURCE_DIR}/common/icon.png)
set(WEBOS_APPINFO ${CMAKE_CURRENT_SOURCE_DIR}/common/appinfo.json.in)
set(WEBOS_BUILD_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/common/build-package.sh)

add_subdirectory(ndl)
add_subdirectory(common)
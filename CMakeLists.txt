cmake_minimum_required(VERSION 3.2)

project(ctrltbx)

set(CTRLTBX_MAJOR_VERSION 0)
set(CTRLTBX_MINOR_VERSION 1)
set(CTRLTBX_PATCH_VERSION 0)
set(CTRLTBX_VERSION ${CTRLTBX_MAJOR_VERSION}.${CTRLTBX_MINOR_VERSION}.${CTRLTBX_PATCH_VERSION})

find_package(SymEngine CONFIG REQUIRED)

add_subdirectory(src)

# install(TARGETS test DESTINATION lib)
# install(FILES test.h DESTINATION include)

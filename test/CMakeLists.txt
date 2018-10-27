# Testing for Controls Library
#
# Testing is enabled by default. To disable testing, use the 'BUILD_TESTS=OFF'
# flag.
#
# Tests use the Catch2 testing framework (https://github.com/catchorg/Catch2).
# See the individual tests for more information.

project(test_basic)

find_package(Catch2 REQUIRED)

include(CTest)

add_executable(test_arit test_main.cc)
target_link_libraries(test_arit symctrl ${SYMENGINE_LIBRARIES} Catch2::Catch2)
add_test(test_arit ${PROJECT_BINARY_DIR}/test_arit)

add_executable(test_ss test_statespace.cc)
target_link_libraries(test_ss symctrl ${SYMENGINE_LIBRARIES} Catch2::Catch2)
add_test(test_ss ${PROJECT_BINARY_DIR}/test_ss)

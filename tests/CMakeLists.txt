enable_testing()
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} csvparse csvgrep expparse)

include_directories(. ../src)

add_executable(test_csvgrep test_csvgrep.c)
target_link_libraries(test_csvgrep ${LIBS} -lpthread)
add_test(test_csvgrep ${CMAKE_CURRENT_BINARY_DIR}/test_csvgrep)
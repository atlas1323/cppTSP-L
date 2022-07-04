project(tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test-run test1.cpp test2.cpp)
target_link_libraries(test-run optimizers)
target_link_libraries(test-run gtest gtest_main)
target_link_libraries(test-run assist)
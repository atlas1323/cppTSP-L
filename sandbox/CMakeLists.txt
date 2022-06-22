add_executable(sandbox-exe sandbox.cpp)

target_link_libraries(sandbox-exe PRIVATE assist)
target_link_libraries(sandbox-exe PRIVATE optimizers)

add_executable(TSP-exe main.cpp)

target_link_libraries(TSP-exe PRIVATE assist)
target_link_libraries(TSP-exe PRIVATE optimizers)

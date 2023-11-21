cmake_minimum_required(VERSION 3.8)
project(CS539_Project)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 ")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(seq_scan_test test/seq_scan_test.cpp)
target_link_libraries(seq_scan_test EXECUTOR)

add_executable(filter_seq_scan_test test/filter_seq_scan_test.cpp)
target_link_libraries(filter_seq_scan_test EXECUTOR)

add_executable(nested_loop_join_test test/nested_loop_join_test.cpp)
target_link_libraries(nested_loop_join_test EXECUTOR)

add_executable(hash_join_test test/hash_join_test.cpp)
target_link_libraries(hash_join_test EXECUTOR)

add_executable(complex_test test/complex_executor_test.cpp)
target_link_libraries(complex_test EXECUTOR)

add_executable(another_complex_test test/another_complex_executor_test.cpp)
target_link_libraries(another_complex_test EXECUTOR)

add_executable(aggregation_test test/aggregation_executor_test.cpp)
target_link_libraries(aggregation_test EXECUTOR)

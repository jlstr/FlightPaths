cmake_minimum_required(VERSION 4.0.2)
project(FlightPaths VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(FlightPaths src/flight_paths.cpp src/graph_builder.cpp src/path_finder.cpp src/data_loader.cpp src/string_helper.cpp)
add_executable(graph_builder_test src/tests/graph_builder_test.cpp src/graph_builder.cpp)
add_executable(data_loader_test src/tests/data_loader_test.cpp src/data_loader.cpp src/string_helper.cpp)
add_executable(path_finder_test src/tests/path_finder_test.cpp src/path_finder.cpp src/string_helper.cpp)
add_executable(string_helper_test src/tests/string_helper_test.cpp src/string_helper.cpp)

target_link_libraries(graph_builder_test GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(data_loader_test GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(path_finder_test GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(string_helper_test GTest::gtest_main GTest::gmock GTest::gmock_main)
target_compile_features(FlightPaths PUBLIC cxx_std_20)

include(GoogleTest)
gtest_discover_tests(graph_builder_test)
gtest_discover_tests(data_loader_test)
gtest_discover_tests(path_finder_test)
gtest_discover_tests(string_helper_test)
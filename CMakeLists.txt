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

add_executable(FlightPaths src/flight_paths.cpp src/graph_builder.cpp src/path_finder.cpp)
add_executable(graph_builder_test src/tests/graph_builder_test.cpp)

target_link_libraries(graph_builder_test GTest::gtest_main)
target_compile_features(FlightPaths PUBLIC cxx_std_20)

include(GoogleTest)
gtest_discover_tests(graph_builder_test)
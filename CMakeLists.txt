cmake_minimum_required(VERSION 3.10.0)
project(FlightPaths VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(FlightPaths src/flight_paths.cpp src/graph_builder.cpp src/path_finder.cpp)

include(CTest)
enable_testing()

target_compile_features(FlightPaths PUBLIC cxx_std_20)
target_link_libraries(FlightPaths GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(FlightPaths)
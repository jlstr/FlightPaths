cmake_minimum_required(VERSION 3.10.0)
project(FlightPaths VERSION 0.1.0 LANGUAGES C CXX)

add_executable(FlightPaths src/flight_paths.cpp src/graph_builder.cpp)

include(CTest)
enable_testing()

target_compile_features(FlightPaths PUBLIC cxx_std_20)
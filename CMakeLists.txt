cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_STANDARD 11)
add_executable(run_manual_benchmarks
        benchmarks/manual_bench.cpp
        src/ExtendedNumerics.cpp)

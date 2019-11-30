cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_STANDARD 11)
add_executable(benchmark_fixnum_bignum_delineation
        benchmarks/fixnum_bignum_delineation.cpp
        src/ExtendedNumerics.cpp)

add_executable(benchmark_time_bignum_ops
               benchmarks/time_bignum_ops.cpp
               src/ExtendedNumerics.cpp)

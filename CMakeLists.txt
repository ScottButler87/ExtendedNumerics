cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.1
)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.5.0
)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

FetchContent_GetProperties(benchmark)
if(NOT benchmark_POPULATED)
    FetchContent_Populate(benchmark)
    add_subdirectory(${benchmark_SOURCE_DIR} ${benchmark_BINARY_DIR})
endif()

include_directories(
        "${benchmark_SOURCE_DIR}/include"
        "${googletest_SOURCE_DIR}/googletest/include")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})


add_executable(run_google_benchmark
        benchmarks/gbench.cpp
        src/ExtendedNumerics.cpp)

add_executable(run_manual_benchmarks
        benchmarks/manual_bench.cpp
        src/ExtendedNumerics.cpp)

target_link_libraries(run_google_benchmark benchmark)

#add_executable(test_extended_numerics
#        src/ExtendedNumerics.cpp
#        tst/ExtendedNumerics.cpp
#        TestDriver.cpp)

#target_link_libraries(test_extended_numerics gtest pthread)

#add_executable(runTests
#        src/ExtendedNumerics.cpp
#        tst/bignum_tests.cpp
#        tst/ratnum_tests.cpp
#        tst/exactnum_tests.cpp
#        TestDriver.cpp)
#src_bak/NumericOperations.h
#src_bak/Fixnum.cpp
#src_bak/Number.h
#src_bak/Fixnum.cpp
#src_bak/Fixnum.h
#src_bak/Ratnum.cpp
#src_bak/Ratnum.h
#src_bak/src_bak.h
#src_bak/util.h
#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

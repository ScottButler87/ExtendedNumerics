cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

#GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(BOOST_ROOT "/usr/lib/x86_64-linux-gnu")

find_package(Boost 1.65.1)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()

add_executable(run_benchmarks
        BenchmarkDriver.cpp
        src/ExtendedNumerics.cpp)

add_executable(test_extended_numerics
        src/ExtendedNumerics.cpp
        tst/ExtendedNumerics.cpp
        TestDriver.cpp)

target_link_libraries(test_extended_numerics ${GTEST_LIBRARIES} pthread)

add_executable(runTests
        src_bak/ExtendedNumerics.hpp
        src_bak/Boost_Bignum.cpp
        src_bak/Boost_Ratnum.cpp
        src_bak/ExactNum.cpp
        tst/bignum_tests.cpp
        tst/ratnum_tests.cpp
        tst/exactnum_tests.cpp
        TestDriver.cpp)
#src_bak/NumericOperations.h
#src_bak/Fixnum.cpp
#src_bak/Number.h
#src_bak/Fixnum.cpp
#src_bak/Fixnum.h
#src_bak/Ratnum.cpp
#src_bak/Ratnum.h
#src_bak/src_bak.h
#src_bak/util.h
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
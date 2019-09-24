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

add_executable(runTests src/Boost_Bignum.h src/Boost_Bignum.cpp src/Boost_Ratnum.h src/Boost_Ratnum.cpp tst/bignum_tests.cpp main.cpp)
#src/NumericOperations.h
#src/Fixnum.cpp
#src/Number.h
#src/Fixnum.cpp
#src/Fixnum.h
#src/Ratnum.cpp
#src/Ratnum.h
#src/src.h
#src/util.h
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
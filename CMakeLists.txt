cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

#GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(runTests main.cpp Number.h src/Bignum.cpp src/Bignum.h tst/bignum_tests.cpp)

#        src/Fixnum.cpp
#        src/Fixnum.h
#        src/Ratnum.cpp
#        src/Ratnum.h
#        src/src.h
#        src/util.h
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
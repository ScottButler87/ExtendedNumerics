cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

set(CMAKE_CXX_STANDARD 17)

add_executable(WasmExtendedNumerics main.cpp Number.h ExtendedNumerics/Fixnum.cpp ExtendedNumerics/Fixnum.h ExtendedNumerics/Bignum.cpp ExtendedNumerics/Bignum.h ExtendedNumerics/Ratnum.cpp ExtendedNumerics/Ratnum.h ExtendedNumerics/ExtendedNumerics.h ExtendedNumerics/util.h)
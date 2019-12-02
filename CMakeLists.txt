cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-4 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -gdwarf-4 -g3 ")
set(CMAKE_CXX_STANDARD 11)

find_package(GMP 6.0.0)
find_package(Boost 1.65.1)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

if(GMP_FOUND)
    include_directories(${GMP_INCLUDES})
endif()

add_executable(benchmark_fixnum_bignum_delineation
        benchmarks/fixnum_bignum_delineation.cpp
        src/ExtendedNumerics.cpp)

add_library(ExtendedNumerics
            src/ExtendedNumerics.cpp)

target_link_libraries(ExtendedNumerics ${GMP_LIBRARIES} ${Boost_LIBRARIES})

add_executable(benchmark_time_bignum_ops
               benchmarks/time_bignum_ops.cpp)
target_link_libraries(benchmark_time_bignum_ops ExtendedNumerics)


add_executable(benchmark_time_ratnum_ops
               benchmarks/time_ratnum_ops.cpp)
target_link_libraries(benchmark_time_ratnum_ops ExtendedNumerics)

add_executable(benchmark_time_exact_complexnum_ops
        benchmarks/time_exact_complexnum_ops.cpp)
target_link_libraries(benchmark_time_exact_complexnum_ops ExtendedNumerics)

#add_executable(benchmark_time_exact_rational_complexnum_ops
#        benchmarks/time_exact_rational_complexnum_ops.cpp)
#target_link_libraries(benchmark_time_exact_complexnum_ops ExtendedNumerics)

#add_executable(benchmark_time_inexact_complexnum_ops
#        benchmarks/time_inexact_rational_complexnum_ops.cpp)
#target_link_libraries(benchmark_time_inexact_complexnum_ops ExtendedNumerics)

add_executable(benchmark_driver
               benchmarks/benchmark_driver.cpp)
target_link_libraries(benchmark_driver ExtendedNumerics)

add_executable(scratchbox
        scratchbox.cpp)
target_link_libraries(scratchbox ExtendedNumerics ${GMP_LIBRARIES} ${Boost_LIBRARIES})
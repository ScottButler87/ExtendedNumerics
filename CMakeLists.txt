cmake_minimum_required(VERSION 3.14)
project(WasmExtendedNumerics)

#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_RELEASE_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-4 -g3 -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_CXX_STANDARD 14)

if (BUILD_WASM)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
	find_package(Boost 1.65.1 REQUIRED)
	if(Boost_FOUND)
		include_directories(${Boost_INCLUDE_DIRS})
	endif()
endif()


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

add_executable(benchmark_fixnum_bignum_int64_t_comparison
		benchmarks/benchmark_bignum_fixnum_int64_t_comparison.cpp
        src/ExtendedNumerics.cpp)

add_library(ExtendedNumerics
		src/ExtendedNumerics.cpp
		src/BignumInternal.cpp
		src/RatnumInternal.cpp
		src/ExactComplexnumInternal.cpp
		src/DynamicDoubleDispatch.cpp
		src/InexactComplexnumInternal.cpp)

target_link_libraries(ExtendedNumerics )

add_executable(benchmark_time_bignum_ops
               benchmarks/time_bignum_ops.cpp)
target_link_libraries(benchmark_time_bignum_ops ExtendedNumerics)


add_executable(benchmark_time_ratnum_ops
               benchmarks/time_ratnum_ops.cpp)
target_link_libraries(benchmark_time_ratnum_ops ExtendedNumerics)

add_executable(benchmark_time_exact_complexnum_ops
        benchmarks/time_exact_complexnum_ops.cpp)
target_link_libraries(benchmark_time_exact_complexnum_ops ExtendedNumerics)

add_executable(benchmark_perf_per_operand_type
        benchmarks/benchmark_perf_per_operand_type.cpp)
target_link_libraries(benchmark_perf_per_operand_type ExtendedNumerics)

add_executable(benchmark_ratnum_numeric_overhead
		benchmarks/benchmark_ratnum_numeric_overhead.cpp)
target_link_libraries(benchmark_ratnum_numeric_overhead ExtendedNumerics)

add_executable(benchmark_operation_symmetry
		benchmarks/benchmark_operation_symmetry.cpp)
target_link_libraries(benchmark_operation_symmetry ExtendedNumerics)

add_executable(benchmark_driver
               benchmarks/benchmark_driver.cpp)
target_link_libraries(benchmark_driver ExtendedNumerics)

add_executable(scratchbox
        scratchbox.cpp )
target_link_libraries(scratchbox ExtendedNumerics)


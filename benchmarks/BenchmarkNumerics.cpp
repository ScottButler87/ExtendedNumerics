#include <iostream>
#include <chrono>
#include "../src/ExtendedNumerics.hpp"
#include "benchmark_settings_and_defs.hpp"

//volatile int64_t no_touchy = 0;
//
//__attribute__((optimize(OPTIMIZATION_FLAGS)))
//double benchmark_loop_overhead() {
//  BENCHMARK_CODE(
//  ;
//  )
//
//  return result;
//}
//
//__attribute__((optimize(OPTIMIZATION_FLAGS)))
//double benchmark_operation_uint64_t() {
//  int64_t a = 1;
//  int64_t b = 2;
//  int64_t intermediate = 0;
//  BENCHMARK_CODE(
//      intermediate <<= intermediate + (a OPERATION b);
//  )
//  no_touchy = static_cast<volatile int64_t>(intermediate);
//
//  return result;
//}
//
//__attribute__((optimize(OPTIMIZATION_FLAGS)))
//double benchmark_operation_numeric_fixnums() {
//  Numeric b("1");
//  Numeric a("2");
//  int64_t intermediate = 0;
//
//  BENCHMARK_CODE(
//      intermediate <<= intermediate + (a OPERATION b);
//  )
//  no_touchy = intermediate;
//
//  return result;
//}
//
//int main() {
//
//  auto result_loop_overhead = benchmark_loop_overhead();
//  std::cout << "Loop overhead: "
//            << result_loop_overhead
//            << std::endl;
//
//  auto result_int64_t = benchmark_operation_uint64_t();
//  std::cout << "int64_t operation time: "
//            << result_int64_t
//            << std::endl;
//
//  auto result_numeric_fixnum = benchmark_operation_numeric_fixnums();
//  std::cout << "numeric_fixnum operation time: "
//            << result_numeric_fixnum
//            << std::endl;
//  return 0;
//}

//static std::string MAX_POSITIVE_FIXNUM_STRING("4611686018427387903");
//static std::string MAX_NEGATIVE_FIXNUM_STRING("-4611686018427387904");
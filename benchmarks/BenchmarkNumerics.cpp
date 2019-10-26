#include <iostream>
#include <chrono>
#include "../src/ExtendedNumerics.hpp"
#include "benchmark_settings_and_defs.hpp"

template<class TimeUnit>
__attribute__((optimize(O3_WITHOUT_DCE_AND_DSE)))
uint64_t benchmark_operation_uint64_t(size_t warm_up_runs,
                                      size_t loop_iterations_per_run,
                                      size_t runs_to_average) {
  int64_t a = 1;
  int64_t b = 1;
  BENCHMARK_CODE(
      (a OPERATION b);,
      warm_up_runs, loop_iterations_per_run, runs_to_average,
      TimeUnit
  )

  return result;
}

template<class TimeUnit>
__attribute__((optimize(O3_WITHOUT_DCE_AND_DSE)))
uint64_t benchmark_loop_overhead(size_t warm_up_runs,
                                 size_t loop_iterations_per_run,
                                 size_t runs_to_average) {
  BENCHMARK_CODE(
      ((void)0);,
      warm_up_runs, loop_iterations_per_run, runs_to_average,
      TimeUnit
  )

  return result;
}

template<class TimeUnit>
__attribute__((optimize(O3_WITHOUT_DCE_AND_DSE)))
uint64_t benchmark_operation_numeric_fixnums(size_t warm_up_runs,
                                             size_t loop_iterations_per_run,
                                             size_t runs_to_average) {
  Numeric b("1");
  Numeric a("2");

  BENCHMARK_CODE(
      (a
      OPERATION
      b);,
      warm_up_runs, loop_iterations_per_run, runs_to_average,
      TimeUnit
  )

  return result;
}

int main() {

  std::cout << "Loop overhead: "
            << benchmark_loop_overhead<UNITS>(WARM_UP_LOOPS, NUM_LOOPS, SAMPLES_TO_AVERAGE)
            << std::endl;

  std::cout << "int64_t operation time: "
            << benchmark_operation_uint64_t<UNITS>(WARM_UP_LOOPS, NUM_LOOPS, SAMPLES_TO_AVERAGE)
            << std::endl;

  std::cout << "numeric_fixnum operation time: "
            << benchmark_operation_numeric_fixnums<UNITS>(WARM_UP_LOOPS, NUM_LOOPS, SAMPLES_TO_AVERAGE)
            << std::endl;
  return 0;
}

//static std::string MAX_POSITIVE_FIXNUM_STRING("4611686018427387903");
//static std::string MAX_NEGATIVE_FIXNUM_STRING("-4611686018427387904");
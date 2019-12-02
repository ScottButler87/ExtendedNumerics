#include <chrono>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include "../src/ExtendedNumerics.hpp"
#include "benchmark_settings_and_defs.hpp"
#include "random_numeric_generators.hpp"
#include "time_benchmark_operation.hpp"

int_fast64_t multiplication_no_fixnum_overflow_left = static_cast<int_fast64_t>(PRNG() % (static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) - 1)) + 1;
int_fast64_t multiplication_no_fixnum_overflow_right = static_cast<int_fast64_t>(PRNG() % (static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) - 1)) + 1;
bool hack_assert0 = (assert(std::sqrt(MAX_FIXNUM_VALUE) > multiplication_no_fixnum_overflow_left
                                 && std::sqrt(MAX_FIXNUM_VALUE) > multiplication_no_fixnum_overflow_right), true);


int_fast64_t multiplication_fixnum_overflow_left = static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) + 1 +
    (PRNG() % 1000);
int_fast64_t multiplication_fixnum_overflow_right = static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) + 1 +
    (PRNG() % 1000);
bool hack_assert1 = (assert(std::sqrt(MAX_FIXNUM_VALUE) < multiplication_fixnum_overflow_left
                                 && std::sqrt(MAX_FIXNUM_VALUE) < multiplication_fixnum_overflow_right), true);

int add_results_fixnum_bignum_delineation(std::ostream &results) {
#define INT64_T_BENCHMARK_CALCULATION (result *= multiplication_no_fixnum_overflow_left * multiplication_no_fixnum_overflow_right)
#define DESCRIBE_INT64_T_BENCHMARK_CALCULATION XSTR(2x multiplications of native integers)
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(FAST_OP_LOOPS_PER_SAMPLE, INT64_T_BENCHMARK_CALCULATION,
        INT64_T_BENCHMARK_CALCULATION, DESCRIBE_INT64_T_BENCHMARK_CALCULATION, false)
  }

#define NUMERIC_FIXNUM_BENCHMARK_CALCULATION (a * b)
#define DESCRIBE_NUMERIC_FIXNUM_BENCHMARK_CALCULATION XSTR(multiplication of two fixnums resulting in a fixnum)
  {
    Numeric a(multiplication_no_fixnum_overflow_left);
    Numeric b(multiplication_no_fixnum_overflow_right);
    WARM_AND_TIME_BENCHMARK_OPERATION(FAST_OP_LOOPS_PER_SAMPLE, NUMERIC_FIXNUM_BENCHMARK_CALCULATION,
        NUMERIC_FIXNUM_BENCHMARK_CALCULATION, DESCRIBE_NUMERIC_FIXNUM_BENCHMARK_CALCULATION, false)
  }

#define NUMERIC_BIGNUM_BENCHMARK_CALCULATION (a * b)
#define DESCRIBE_NUMERIC_BIGNUM_BENCHMARK_CALCULATION XSTR(multiplication of two fixnums overflowing into a bignum)
  {
    Numeric a(multiplication_fixnum_overflow_left);
    Numeric b(multiplication_fixnum_overflow_right);

    WARM_AND_TIME_BENCHMARK_OPERATION(MEDIUM_OP_LOOPS_PER_SAMPLE, NUMERIC_BIGNUM_BENCHMARK_CALCULATION,
        NUMERIC_BIGNUM_BENCHMARK_CALCULATION, DESCRIBE_NUMERIC_BIGNUM_BENCHMARK_CALCULATION, false)
  }

  return 0;
}

int main () {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

  std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

  //TODO add results to string stream after running benchmarks above
  add_results_fixnum_bignum_delineation(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();

  return 0;
}
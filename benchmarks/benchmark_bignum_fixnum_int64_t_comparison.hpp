#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_BIGNUM_FIXNUM_INT64_T_COMPARISON_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_BIGNUM_FIXNUM_INT64_T_COMPARISON_HPP_

#include <chrono>
#include <iostream>
#include "../src/Numeric.hpp"
#include "_benchmark_settings_and_defs.hpp"
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

#define ADD_DELINEATION_COMPARISON_RESULT(OPERAND_TYPE, AVG_TIME, LOOPS_PER_SAMPLE, RESULTS_OSTREAM) \
RESULTS_OSTREAM << std::setw(DESCRIPTION_WIDTH) << XSTR(OPERAND_TYPE)\
                << std::setw(TIME_PER_OPERATION_COLUMN_SIZE) << std::setprecision(4)\
                << TIME_PER_OPERATION_TO_STRING(AVG_TIME_TO_PER_OPERATION_TIME(AVG_TIME, LOOPS_PER_SAMPLE)) << std::endl\
                << std::setprecision(6);

void add_results_fixnum_bignum_delineation(std::ostream &results) {
  results << "Fixnum/Bignum/int64_t performance comparison (multiplication baseline):" << std::endl << std::endl;

  std::chrono::TIME_UNITS int64_t_avg_time;
  std::chrono::TIME_UNITS fixnum_avg_time;
  std::chrono::TIME_UNITS bignum_avg_time;

#define NUMERIC_BIGNUM_BENCHMARK_CALCULATION (a * b)
#define DESCRIBE_NUMERIC_BIGNUM_BENCHMARK_CALCULATION XSTR(multiplication of two fixnums overflowing into a bignum)
  {
    Numeric a(multiplication_fixnum_overflow_left);
    Numeric b(multiplication_fixnum_overflow_right);

    WARM_AND_TIME_BENCHMARK_OPERATION((10 * MEDIUM_OP_LOOPS_PER_SAMPLE), NUMERIC_BIGNUM_BENCHMARK_CALCULATION,
                                      NUMERIC_BIGNUM_BENCHMARK_CALCULATION, DESCRIBE_NUMERIC_BIGNUM_BENCHMARK_CALCULATION, BE_VERBOSE)
    bignum_avg_time = avg_time;
  }

#define NUMERIC_FIXNUM_BENCHMARK_CALCULATION (a * b)
#define DESCRIBE_NUMERIC_FIXNUM_BENCHMARK_CALCULATION XSTR(multiplication of two fixnums resulting in a fixnum)
  {
    Numeric a(multiplication_no_fixnum_overflow_left);
    Numeric b(multiplication_no_fixnum_overflow_right);
    WARM_AND_TIME_BENCHMARK_OPERATION((100 * TRIVIAL_OP_LOOPS_PER_SAMPLE), NUMERIC_FIXNUM_BENCHMARK_CALCULATION,
                                      NUMERIC_FIXNUM_BENCHMARK_CALCULATION, DESCRIBE_NUMERIC_FIXNUM_BENCHMARK_CALCULATION, BE_VERBOSE)
    fixnum_avg_time = avg_time;
  }

#define INT64_T_BENCHMARK_CALCULATION (result *= multiplication_no_fixnum_overflow_left * multiplication_no_fixnum_overflow_right)
#define DESCRIBE_INT64_T_BENCHMARK_CALCULATION XSTR(2x multiplications of native integers)
  {
    WARM_AND_TIME_BENCHMARK_OPERATION((100 * TRIVIAL_OP_LOOPS_PER_SAMPLE), INT64_T_BENCHMARK_CALCULATION,
                                      INT64_T_BENCHMARK_CALCULATION, DESCRIBE_INT64_T_BENCHMARK_CALCULATION, BE_VERBOSE)
    int64_t_avg_time = avg_time;
  }

  // intentionally doubling loops per sample here to compensate for the necessity of multiplying int64_t twice to
  // prevent compiler optimization
  ADD_DELINEATION_COMPARISON_RESULT(int64_t, int64_t_avg_time, (200 * TRIVIAL_OP_LOOPS_PER_SAMPLE), results)
  ADD_DELINEATION_COMPARISON_RESULT(fixnum, fixnum_avg_time, (100 * TRIVIAL_OP_LOOPS_PER_SAMPLE), results)
  ADD_DELINEATION_COMPARISON_RESULT(bignum, bignum_avg_time, (10 * MEDIUM_OP_LOOPS_PER_SAMPLE), results)
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_BIGNUM_FIXNUM_INT64_T_COMPARISON_HPP_

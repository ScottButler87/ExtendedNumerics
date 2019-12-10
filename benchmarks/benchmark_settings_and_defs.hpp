//
// Created by scott on 10/25/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

#include <chrono>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include "../src/ExtendedNumerics.hpp"

//TODO Change benchmarks to use different number of same bit size each sample? Collaterally, will function be badly cooled?

/* Centralized optimization blockers */
volatile uint64_t do_not_optimize = 0;
static int64_t result;
static Numeric result2(static_cast<int64_t>(0));

#define BE_VERBOSE true
#define BE_SILENT false
#define PERFORM_DOUBLING_BEHAVIOR_BENCHMARKS true
#define PERFORM_PERFORMANCE_PER_OPERAND_BENCHMARKS true
#define PERFORM_OPERATION_SYMMETRY_BENCHMARKS true
#define PERFORM_RATNUM_NUMERIC_OVERHEAD_BENCHMARK true
#define PERFORM_FIXNUM_BIGNUM_INT64_T_COMPARISON_BENCHMARKS true
#define TRIVIALIZE_BENCHMARKS_TO_EMPHASIZE_OUTPUT false
#define SEED_RANDOM_NUMBER_GENERATOR true

#if SEED_RANDOM_NUMBER_GENERATOR
  #define RANDOM_SEED_NUMBER 9439832
#else
  #define RANDOM_SEED_NUMBER dev()
#endif

#define WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME 128
#define DESCRIPTION_OF_RATIO_THRESHOLD XSTR(1/WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME)
#define WARMING_THRESHOLD static_cast<double>(1)/WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME
#define NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING 5

#define TIME_UNITS nanoseconds
#define PER_OP_TIME_UNITS nanoseconds
#define PER_OP_TIME_UNIT_ABBREVIATION ns
#define LARGE_TIME_UNITS seconds

#define DOUBLING_BEHAVIOR_INPUT_BIT_COLUMN_SIZE 16
#define TIME_PER_OPERATION_COLUMN_SIZE 21
#define DOUBLING_BEHAVIOR_RATIO_COLUMN_SIZE 9
#define DOUBLING_BEHAVIOR_RATIO_SIG_FIGS 5

#define PERF_PER_OPERAND_OPERATION_COLUMN_SIZE 18
#define PERF_PER_OPERAND_OPERAND_COLUMN_SIZE 20
#define PERF_PER_OPERAND_FIXNUM_SIZE 61
#define PERF_PER_OPERAND_BIGNUM_SIZE 144
#define PERF_PER_OPERAND_RATNUM_SIZE 77

#if TRIVIALIZE_BENCHMARKS_TO_EMPHASIZE_OUTPUT
  #define SAMPLES_TO_AVERAGE 1
  #define BASE_OP_LOOPS_PER_SAMPLE 1
  bool hack_static_warning = (
      std::cerr << "WARNING! Benchmarks are trivialized to emphasize output. Not valid results!" << std::endl
      << std::endl << std::flush,
      true);
  #define BIGNUM_ADDITION_SUBTRACTION_BASE_BIT_SIZE 67
  #define BIGNUM_MULTIPLICATION_BASE_BIT_SIZE 67
  #define BIGNUM_DIVISION_BASE_BIT_SIZE 67
  #define RATIONAL_NUMBER_BIT_SIZE 67
#else
  #define SAMPLES_TO_AVERAGE 500
  #define BASE_OP_LOOPS_PER_SAMPLE 100
  
  
  #define BIGNUM_MULTIPLICATION_BASE_BIT_SIZE 346
  #define BIGNUM_ADDITION_SUBTRACTION_BASE_BIT_SIZE 346
  #define BIGNUM_DIVISION_BASE_BIT_SIZE 346
  
  // These seem to be horrendously slow in comparison to integers, and apparently take the same amount of time for
  // any operation
  #define RATIONAL_NUMBER_BIT_SIZE 173
  
  #define NON_TRIVIAL_RUN
#endif

// these back the macros to allow arbitrary operations on relative sizes without runtime cost
// arbitrary precision mult/div involving ratnums
static constexpr int const& slow_op_loops_per_sample = BASE_OP_LOOPS_PER_SAMPLE;
// arbitrary precision add/sub involving ratnums, mult involving bignums
static constexpr int const& medium_op_loops_per_sample = 10 * slow_op_loops_per_sample;
// arbitrary precision add/sub/div involving bignums
static constexpr int const& fast_op_loops_per_sample = 20 * medium_op_loops_per_sample;
// fixed width operations
static constexpr int const& trivial_op_loops_per_sample = 10 * fast_op_loops_per_sample;

#define SLOW_OP_LOOPS_PER_SAMPLE   slow_op_loops_per_sample
#define MEDIUM_OP_LOOPS_PER_SAMPLE medium_op_loops_per_sample
#define FAST_OP_LOOPS_PER_SAMPLE   fast_op_loops_per_sample
//
#define TRIVIAL_OP_LOOPS_PER_SAMPLE (10 * fast_op_loops_per_sample)

#define STR(TO_STRINGIFY) #TO_STRINGIFY
// expands macro once before stringifying
#define XSTR(TO_STRINGIFY) STR(TO_STRINGIFY)
#define XSTR_LOWER(TO_STRINGIFY_LOWERCASE) boost::algorithm::to_lower_copy(std::string(XSTR(TO_STRINGIFY_LOWERCASE)))

#define REPEAT_N_TIMES(TIMES, OPERATION)\
for (int i = 0; i < TIMES; ++i) {\
  (OPERATION);\
}

#define DESCRIPTION_WIDTH 28

#ifdef NON_TRIVIAL_RUN
bool hack_static_print_benchmark_info = (
      std::cout << "Loops per sample for" << std::endl
                << std::setw(DESCRIPTION_WIDTH) << "Slow speed operations: " << slow_op_loops_per_sample << std::endl
                << std::setw(DESCRIPTION_WIDTH) << "Medium speed operations: " << medium_op_loops_per_sample << std::endl
                << std::setw(DESCRIPTION_WIDTH) << "Quick speed operations: " << fast_op_loops_per_sample << std::endl
                << std::endl
                << "Samples averaged per benchmark: " << SAMPLES_TO_AVERAGE << std::endl << std::endl
                << (PERFORM_DOUBLING_BEHAVIOR_BENCHMARKS ?
                    (dynamic_cast<std::stringstream&&>(std::stringstream()
                        << "Doubling behavior bignum bit sizes" << std::endl << std::endl
                        << std::setw(DESCRIPTION_WIDTH) << "addition/subtraction" << std::setw(4)
                        << BIGNUM_ADDITION_SUBTRACTION_BASE_BIT_SIZE << std::endl
                        << std::setw(DESCRIPTION_WIDTH) << "multiplication" << std::setw(4)
                        << BIGNUM_MULTIPLICATION_BASE_BIT_SIZE << std::endl
                        << std::setw(DESCRIPTION_WIDTH) << "division" << std::setw(4)
                        << BIGNUM_DIVISION_BASE_BIT_SIZE << std::endl
                    )).str() : "")  << std::endl
                << (PERFORM_DOUBLING_BEHAVIOR_BENCHMARKS ?
                    (dynamic_cast<std::stringstream&&>(std::stringstream()
                        << "Operation performance comparison operand sizes" << std::endl << std::endl
                        << std::setw(DESCRIPTION_WIDTH) << "fixnum" << std::setw(4)
                        << PERF_PER_OPERAND_FIXNUM_SIZE << std::endl
                        <<  std::setw(DESCRIPTION_WIDTH) << "bignum" << std::setw(4)
                        << PERF_PER_OPERAND_BIGNUM_SIZE << std::endl
                        << std::setw(DESCRIPTION_WIDTH) << "ratnum" << std::setw(4)
                        << PERF_PER_OPERAND_RATNUM_SIZE << std::endl
                    )).str() : "")
                << std::endl << std::flush, true);
#endif

#define STATE_WARMING_CONDITIONS \
std::cout << "Calculation warming repeatedly runs the calculation until "\
    << NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING\
    << " back to back iterations' execution times" << std::endl << "are relatively close, maxing out at"\
    << " the number of loops per iteration." << std::endl << std::endl << "Threshold: delta less than "\
    << DESCRIPTION_OF_RATIO_THRESHOLD << " of preceeding run-time." << std::endl << std::endl;

#define AVG_TIME_TO_PER_OPERATION_TIME(AVG_TIME, LOOPS_PER_SAMPLE) \
(static_cast<double>(std::chrono::duration_cast<std::chrono::PER_OP_TIME_UNITS>(AVG_TIME).count())/ LOOPS_PER_SAMPLE)

#define TIME_PER_OPERATION_TO_STRING(TIME_PER_OPERATION) \
(dynamic_cast<std::ostringstream&&>(std::ostringstream("") << std::fixed << std::setprecision(2) << TIME_PER_OPERATION\
                                                           << " " << XSTR(PER_OP_TIME_UNIT_ABBREVIATION)).str() )

#define IN_LARGE_TIME_UNITS(STD_CHRONO_TIME_UNITS) \
std::chrono::duration_cast<std::chrono::LARGE_TIME_UNITS>(STD_CHRONO_TIME_UNITS).count()

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

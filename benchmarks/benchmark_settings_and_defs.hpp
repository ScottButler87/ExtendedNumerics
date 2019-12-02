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

/* Centralized optimization blockers */
volatile uint64_t do_not_optimize = 0;
static uint_fast64_t result;
static Numeric result2(static_cast<int64_t>(0));


#define TIME_UNITS nanoseconds
#define PER_OP_TIME_UNITS nanoseconds
#define PER_OP_TIME_UNIT_ABBREVIATION ns
#define LARGE_TIME_UNITS seconds

#define TRIVIALIZE_BENCHMARKS_TO_EMPHASIZE_OUTPUT false

#if TRIVIALIZE_BENCHMARKS_TO_EMPHASIZE_OUTPUT
  #define SAMPLES_TO_AVERAGE 10
  #define BASE_OP_LOOPS_PER_SAMPLE 10
  bool hack_static_warning = (
      std::cerr << "WARNING! Benchmarks are trivialized to emphasize output. Not valid results!" << std::endl
      << std::endl << std::flush,

      true);
  #define DIVISION_BASE_BIT_SIZE 65
  #define MULTIPLICATION_BASE_BIT_SIZE 102
  #define ADDITION_SUBTRACTION_BASE_BIT_SIZE MULTIPLICATION_BASE_BIT_SIZE * 8
#else
  #define SAMPLES_TO_AVERAGE 500
  #define BASE_OP_LOOPS_PER_SAMPLE 100

  // slowest operation
  #define DIVISION_BASE_BIT_SIZE 137
  #define MULTIPLICATION_BASE_BIT_SIZE 400
  // make other ops take approx as long per timing as the 8x multiplication does
  #define ADDITION_SUBTRACTION_BASE_BIT_SIZE MULTIPLICATION_BASE_BIT_SIZE * 32

  // These seem to be horrendously slow in comparison to integers, and apparently take the same amount of time for
  // any operation
  #define RATIONAL_NUMBER_BIT_SIZE 350

  #define NON_TRIVIAL_RUN
#endif

static constexpr int const& slow_op_loops_per_sample = BASE_OP_LOOPS_PER_SAMPLE; // O(n^2) or worse operations
static constexpr int const& medium_op_loops_per_sample = slow_op_loops_per_sample * slow_op_loops_per_sample; // O(n)
static constexpr int const& fast_op_loops_per_sample = 100 * medium_op_loops_per_sample; // ~100 * O(n)

#define SLOW_OP_LOOPS_PER_SAMPLE   slow_op_loops_per_sample
#define MEDIUM_OP_LOOPS_PER_SAMPLE medium_op_loops_per_sample
#define FAST_OP_LOOPS_PER_SAMPLE   fast_op_loops_per_sample

#ifdef NON_TRIVIAL_RUN
bool hack_static_print_loop_numbers = (
      std::cout << "Loops per sample for\n"
                << "\t" << std::setw(28) << "Slow speed operations: " << slow_op_loops_per_sample << std::endl
                << "\t" << std::setw(28) << "Medium speed operations: " << medium_op_loops_per_sample << std::endl
                << "\t" << std::setw(28) << "Quick speed operations: " << fast_op_loops_per_sample << std::endl
                << std::endl << std::flush, true);
#endif

#define WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME 128
#define DESCRIPTION_OF_RATIO_THRESHOLD XSTR(1/WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME)
#define WARMING_THRESHOLD static_cast<double>(1)/WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME
#define NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING 4

#define BE_VERBOSE false
#define BE_SILENT false

#define STR(TO_STRINGIFY) #TO_STRINGIFY
// expands macro once before stringifying
#define XSTR(TO_STRINGIFY) STR(TO_STRINGIFY)
#define XSTR_LOWER(TO_STRINGIFY_LOWERCASE) boost::algorithm::to_lower_copy(std::string(XSTR(TO_STRINGIFY_LOWERCASE)))

#define REPEAT_N_TIMES(TIMES, OPERATION)\
for (int i = 0; i < TIMES; ++i) {\
  (OPERATION);\
}

#define STATE_WARMING_CONDITIONS \
std::cout << "Calculation warming repeatedly runs the calculation until "\
    << NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING\
    << " back to back iterations' execution times" << std::endl << "are relatively close, maxing out at"\
    << " the number of loops per iteration." << std::endl << std::endl << "Threshold: delta less than "\
    << DESCRIPTION_OF_RATIO_THRESHOLD << " of preceeding run-time." << std::endl << std::endl;

#define AVG_TIME_TO_PER_OPERATION_TIME(AVG_TIME, LOOPS_PER_SAMPLE) \
(static_cast<double>(std::chrono::duration_cast<std::chrono::PER_OP_TIME_UNITS>(AVG_TIME).count())/ LOOPS_PER_SAMPLE)

#define TIME_PER_OPERATION_TO_STRING(TIME_PER_OPERATION) \
(dynamic_cast<std::ostringstream&>(std::ostringstream("") << std::fixed << std::setprecision(2) << TIME_PER_OPERATION\
                              << " " << XSTR(PER_OP_TIME_UNIT_ABBREVIATION)).str() )

#define IN_LARGE_TIME_UNITS(STD_CHRONO_TIME_UNITS) \
std::chrono::duration_cast<std::chrono::LARGE_TIME_UNITS>(STD_CHRONO_TIME_UNITS).count()

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

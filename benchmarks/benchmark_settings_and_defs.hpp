//
// Created by scott on 10/25/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

#include <chrono>

#define TIME_UNITS nanoseconds
#define FINAL_UNITS nanoseconds

typedef std::chrono::TIME_UNITS time_units;
typedef std::chrono::FINAL_UNITS report_units;

#define SAMPLES 500
#define FAST_OP_LOOPS_PER_SAMPLE 10000000
#define MEDIUM_OP_LOOPS_PER_SAMPLE 100000
#define SLOW_OP_LOOPS_PER_SAMPLE 100000

#define WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME 256
#define DESCRIPTION_OF_RATIO_THRESHOLD XSTR(1/WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME)
#define WARMING_THRESHOLD static_cast<double>(1)/WARMING_THRESHOLD_EXECUTION_WITHIN_ONE_OVER___OF_PREVIOUS_TIME
#define NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING 4

#define ADDITION_SUBTRACTION_BASE_BIT_SIZE 2021
#define MULTIPLICATION_DIVISION_BASE_BIT_SIZE 1029

#define BE_VERBOSE true

#define XSTR(TO_STRINGIFY) STR(TO_STRINGIFY)
#define STR(TO_STRINGIFY) #TO_STRINGIFY

#define REPEAT_TIMES(TIMES, OPERATION)\
for (int i = 0; i < TIMES; ++i) {\
  (OPERATION);\
}

#define LOOP_REPEAT_FAST_OP(OP)\
for (int i = 0; i < FAST_OP_LOOPS_PER_SAMPLE; ++i) {\
  (OP);\
}

#define LOOP_REPEAT_SLOW_OP(OP)\
for (int i = 0; i < SLOW_OP_LOOPS_PER_SAMPLE; ++i) {\
  (OP);\
}

volatile uint64_t do_not_optimize = 0;
static uint_fast64_t result;
static Numeric result2(static_cast<int64_t>(0));

#define STATE_WARMING_CONDITIONS \
    std::cout << "Calculation warming repeatedly runs the calculation until "\
        << NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING\
        << " back to back iterations' execution times are relatively close. Threshold: delta less than "\
        << DESCRIPTION_OF_RATIO_THRESHOLD << " of preceeding run-time." << std::endl;

/**
 * Produces two values, time_sum (total time running) and avg_time (time per full iteration)
 */
#define TIME_BENCHMARK_OPERATION(LOOPS_PER_ITERATION, BENCHMARK_OPERATION, DESCRIPTION, VERBOSE)\
  if (VERBOSE) std::cout << "Warming calculation: " <<  DESCRIPTION << " ... ";\
  auto previous_time =\
      std::chrono::duration_cast<std::chrono::nanoseconds>(\
        std::chrono::nanoseconds(1000));\
  auto threshold = WARMING_THRESHOLD;\
  auto ratio = INFINITY;\
  auto back_to_back_warm_iterations = 0;\
  auto total_warming_count = 0;\
  while (back_to_back_warm_iterations < NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING) {\
    auto start = std::chrono::high_resolution_clock::now();\
    REPEAT_TIMES(LOOPS_PER_ITERATION, BENCHMARK_OPERATION)\
    auto end = std::chrono::high_resolution_clock::now();\
    auto current_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);\
    ratio = (static_cast<double>(previous_time.count()) / current_time.count());\
    result = result - std::move(result2);\
    do_not_optimize += result;\
    previous_time = current_time;\
    ++total_warming_count;\
    if (abs(ratio - 1) < threshold) back_to_back_warm_iterations++; else back_to_back_warm_iterations = 0;\
  }\
  if (VERBOSE) {\
    std::cout << "Finished. Total warming iterations: " << total_warming_count << std::endl;\
        }\
  auto time_sum =\
      std::chrono::duration_cast<std::chrono::TIME_UNITS>(std::chrono::high_resolution_clock::duration::zero());\
  for (size_t h = 0; h < SAMPLES; ++h) {\
    auto start = std::chrono::high_resolution_clock::now();\
    REPEAT_TIMES(LOOPS_PER_ITERATION, BENCHMARK_OPERATION)\
    auto end = std::chrono::high_resolution_clock::now();\
    result = result - std::move(result2);\
    do_not_optimize += result;\
    time_sum += std::chrono::duration_cast<std::chrono::TIME_UNITS>(end - start);\
  }\
  auto avg_time = time_sum / SAMPLES;\
  if (VERBOSE) {\
    std::cout << "Each calculation took "\
              << static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(avg_time).count()) / LOOPS_PER_ITERATION\
              << " " << XSTR(FINAL_UNITS) << std::endl << std::endl;\
              }

#define AVG_TIME_TO_PER_OPERATION_TIME(AVG_TIME, LOOPS_PER_SAMPLE) \
(static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(AVG_TIME).count())/ LOOPS_PER_SAMPLE)

#define DOUBLING_BEHAVIOR_HEADER(OPERAND_TYPE, OPERATION_NAME) \
std::cout << std::right\
          << "Doubling behavior for " << XSTR(OPERAND_TYPE) << " " << XSTR(OPERATION_NAME) << ":" << std::endl\
          << std::endl\
          << std::setw(20) << "Input bit size" << std::setw(20) << "Time per operation"\
          << std::setw(8) << "Ratio" << std::endl;

#define DOUBLING_BEHAVIOR_FIRST_ROW(INPUT_BIT_SIZE, TIME_PER_OPERATION) \
std::cout << std::right\
          << std::setw(20) << INPUT_BIT_SIZE << std::setw(20) << TIME_PER_OPERATION << std::endl;

#define DOUBLING_BEHAVIOR_ADDITIONAL_ROW(INPUT_BIT_SIZE, TIME_PER_OPERATION, LAST_TIME_PER_OPERATION) \
std::cout << std::right\
          << std::setw(20) << INPUT_BIT_SIZE << std::setw(20) << TIME_PER_OPERATION\
          << std::setw(8) << std::showpoint << TIME_PER_OPERATION / LAST_TIME_PER_OPERATION << std::endl\
          << std::noshowpoint;


/* REQUIREMENT |=> random_OPERAND_TYPE fuction is defined (should be in random_numeric_generators.hpp)
   REQUIREMENT |=> DESCRIPTION_GENERATOR should be a macro taking description name, operation name, and operand size */
#define DEMO_DOUBLING_BEHAVIOR(LOOPS_PER_SAMPLE, OPERAND_TYPE,\
      BINARY_OP, OPERATION_NAME, DESCRIPTION_GENERATOR, BASE_BIT_SIZE, MAKE_VERBOSE) \
{\
  Numeric OPERAND_TYPE##_left_base = random_##OPERAND_TYPE(BASE_BIT_SIZE);\
  Numeric OPERAND_TYPE##_right_base = random_##OPERAND_TYPE(BASE_BIT_SIZE);\
  Numeric OPERAND_TYPE##_left_2x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 2);\
  Numeric OPERAND_TYPE##_right_2x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 2);\
  Numeric OPERAND_TYPE##_left_4x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 4);\
  Numeric OPERAND_TYPE##_right_4x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 4);\
  Numeric OPERAND_TYPE##_left_8x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 8);\
  Numeric OPERAND_TYPE##_right_8x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 8);\
  Numeric OPERAND_TYPE##_left_16x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 16);\
  Numeric OPERAND_TYPE##_right_16x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 16);\
  \
  DESCRIPTION_GENERATOR(description_base, OPERATION_NAME, BASE_BIT_SIZE)\
  DESCRIPTION_GENERATOR(description_2x, OPERATION_NAME, BASE_BIT_SIZE * 2)\
  DESCRIPTION_GENERATOR(description_4x, OPERATION_NAME, BASE_BIT_SIZE * 4)\
  DESCRIPTION_GENERATOR(description_8x, OPERATION_NAME, BASE_BIT_SIZE * 8)\
  DESCRIPTION_GENERATOR(description_16x, OPERATION_NAME, BASE_BIT_SIZE * 16)\
  std::chrono::TIME_UNITS avg_time_base;\
  std::chrono::TIME_UNITS avg_time_2x;\
  std::chrono::TIME_UNITS avg_time_4x;\
  std::chrono::TIME_UNITS avg_time_8x;\
  std::chrono::TIME_UNITS avg_time_16x;\
  {\
    /* RESULT |=> calculates time_sum (total_runtime) and avg_time (time per full iteration) */ \
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_base BINARY_OP OPERAND_TYPE##_right_base,\
                             description_base.str(), MAKE_VERBOSE)\
    avg_time_base = avg_time;\
  }\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE,  OPERAND_TYPE##_left_2x BINARY_OP OPERAND_TYPE##_right_2x,\
                             description_2x.str(), MAKE_VERBOSE)\
    avg_time_2x = avg_time;\
  }\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_4x BINARY_OP OPERAND_TYPE##_right_4x,\
                             description_4x.str(), MAKE_VERBOSE)\
    avg_time_4x = avg_time;\
  }\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_8x BINARY_OP OPERAND_TYPE##_right_8x,\
                             description_8x.str(), MAKE_VERBOSE)\
    avg_time_8x = avg_time;\
  }\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_16x BINARY_OP OPERAND_TYPE##_right_16x,\
                             description_16x.str(), MAKE_VERBOSE)\
    avg_time_16x = avg_time;\
  }\
  double per_op_time_base = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_base, LOOPS_PER_SAMPLE);\
  double per_op_time_2x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_2x, LOOPS_PER_SAMPLE);\
  double per_op_time_4x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_4x, LOOPS_PER_SAMPLE);\
  double per_op_time_8x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_8x, LOOPS_PER_SAMPLE);\
  double per_op_time_16x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_16x, LOOPS_PER_SAMPLE);\
  DOUBLING_BEHAVIOR_HEADER(OPERAND_TYPE, OPERATION_NAME)\
  DOUBLING_BEHAVIOR_FIRST_ROW(BASE_BIT_SIZE, per_op_time_base)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 2, per_op_time_2x, per_op_time_base)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 4, per_op_time_4x, per_op_time_2x)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 8, per_op_time_8x, per_op_time_4x)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 16, per_op_time_16x, per_op_time_16x)\
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

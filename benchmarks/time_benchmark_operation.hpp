//
// Created by scott on 11/30/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_BENCHMARK_OPERATION_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_BENCHMARK_OPERATION_HPP_

#include "benchmark_settings_and_defs.hpp"

/**
 * Produces two values, time_sum (total time running) and avg_time (time per full iteration)
 */
#define TIME_BENCHMARK_OPERATION(LOOPS_PER_ITERATION, BENCHMARK_OPERATION, DESCRIPTION, VERBOSE)\
  if (VERBOSE) std::cout << "Warming calculation " << DESCRIPTION << " ... " << std::flush;\
  auto previous_time =\
      std::chrono::duration_cast<std::chrono::nanoseconds>(\
        std::chrono::nanoseconds(1000));\
  auto threshold = WARMING_THRESHOLD;\
  auto ratio = INFINITY;\
  auto back_to_back_warm_iterations = 0;\
  auto total_warming_count = 0;\
  while (total_warming_count < LOOPS_PER_ITERATION &&\
  back_to_back_warm_iterations < NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING) {\
    auto start = std::chrono::high_resolution_clock::now();\
    REPEAT_N_TIMES(LOOPS_PER_ITERATION, BENCHMARK_OPERATION)\
    auto end = std::chrono::high_resolution_clock::now();\
    auto current_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);\
    ratio = (static_cast<double>(previous_time.count()) / current_time.count());\
    result = result - std::move(result2);\
    do_not_optimize += result;\
    previous_time = current_time;\
    ++total_warming_count;\
    if (abs(ratio - 1) < threshold) back_to_back_warm_iterations++; else back_to_back_warm_iterations = 0;\
  }\
  if (VERBOSE) std::cout << "finished. Total warming iterations: " << total_warming_count << std::endl;\
  auto time_sum =\
      std::chrono::duration_cast<std::chrono::TIME_UNITS>(std::chrono::high_resolution_clock::duration::zero());\
  for (size_t h = 0; h < SAMPLES_TO_AVERAGE; ++h) {\
    auto start = std::chrono::high_resolution_clock::now();\
    REPEAT_N_TIMES(LOOPS_PER_ITERATION, BENCHMARK_OPERATION)\
    auto end = std::chrono::high_resolution_clock::now();\
    result = result - std::move(result2);\
    do_not_optimize += result;\
    time_sum += std::chrono::duration_cast<std::chrono::TIME_UNITS>(end - start);\
  }\
  auto avg_time = time_sum / SAMPLES_TO_AVERAGE;\
  if (VERBOSE) std::cout << "Each calculation took "\
              << AVG_TIME_TO_PER_OPERATION_TIME(avg_time, LOOPS_PER_ITERATION) << " "\
              << XSTR(PER_OP_TIME_UNITS) << std::endl\
              << std::endl;

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_BENCHMARK_OPERATION_HPP_

//
// Created by scott on 10/25/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

#define TIME_UNITS nanoseconds
#define FINAL_UNITS nanoseconds
#define SAMPLES 500
#define FAST_OP_LOOPS_PER_SAMPLE 10000000
#define SLOW_OP_LOOPS_PER_SAMPLE 100000
#define BACK_TO_BACK_ITERATION_TIME_RATIO_THRESHOLD_TO_BE_CONSIDERED_WARMED 1.0/256
#define NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING 4

#define XSTR(TO_STRINGIFY) STR(TO_STRINGIFY)
#define STR(TO_STRINGIFY) #TO_STRINGIFY

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

#define TIME_BENCHMARK_OPERATION(BENCHMARK_OPERATION)\
  auto previous_time =\
      std::chrono::duration_cast<std::chrono::nanoseconds>(\
        std::chrono::nanoseconds(1000));\
  auto threshold = BACK_TO_BACK_ITERATION_TIME_RATIO_THRESHOLD_TO_BE_CONSIDERED_WARMED;\
  auto ratio = INFINITY;\
  auto back_to_back_warm_iterations = 0;\
  auto total_warming_count = 0;\
  while (back_to_back_warm_iterations < NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING) {\
    auto start = std::chrono::high_resolution_clock::now();\
    BENCHMARK_OPERATION\
    auto end = std::chrono::high_resolution_clock::now();\
    auto current_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);\
    ratio = (static_cast<double>(previous_time.count()) / current_time.count());\
    result = result - std::move(result2);\
    do_not_optimize += result;\
    previous_time = current_time;\
    ++total_warming_count;\
    if (abs(ratio - 1) < threshold) back_to_back_warm_iterations++; else back_to_back_warm_iterations = 0;\
  }\
  std::cout << "Finished warming, waited for "\
        << NUMBER_OF_CONSECUTIVE_WARMED_ITERATIONS_REQUIRED_TO_BEGIN_BENCHMARKING\
        << " back to back iterations to be warm, threshold "\
        << BACK_TO_BACK_ITERATION_TIME_RATIO_THRESHOLD_TO_BE_CONSIDERED_WARMED << ". Total warming iterations: "\
        << total_warming_count << std::endl;\
  auto time_sum =\
      std::chrono::duration_cast<std::chrono::TIME_UNITS>(std::chrono::high_resolution_clock::duration::zero());\
  for (size_t h = 0; h < SAMPLES; ++h) {\
    auto start = std::chrono::high_resolution_clock::now();\
    BENCHMARK_OPERATION\
    auto end = std::chrono::high_resolution_clock::now();\
    result = result - std::move(result2);\
    do_not_optimize += result;\
    time_sum += std::chrono::duration_cast<std::chrono::TIME_UNITS>(end - start);\
  }\
  auto avg_time = time_sum / SAMPLES;

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

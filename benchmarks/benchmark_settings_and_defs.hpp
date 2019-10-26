//
// Created by scott on 10/25/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

#define NUM_LOOPS (1u << 24u)
#define SAMPLES_TO_AVERAGE 40
#define WARM_UP_LOOPS 40
#define OPERATION +
#define UNITS std::chrono::nanoseconds
#define O3_WITHOUT_DCE_AND_DSE \
"O1"



#define BENCHMARK_CODE(CODE_TO_BENCHMARK, NUM_WARMUP_RUNS, NUM_LOOP_ITERS_PER_RUN, NUM_RUNS_TO_AVG, TIME_UNITS)\
auto sum = std::chrono::high_resolution_clock::duration::zero();\
for (size_t warmups = 0; warmups < NUM_WARMUP_RUNS; ++warmups) {\
  auto start = std::chrono::high_resolution_clock::now();\
  for (size_t i = 0; i < NUM_LOOP_ITERS_PER_RUN; ++i) {\
    CODE_TO_BENCHMARK\
  }\
  auto end = std::chrono::high_resolution_clock::now();\
  sum += (end - start);\
}\
auto warmup_time = std::chrono::duration_cast<TIME_UNITS>(sum / NUM_RUNS_TO_AVG).count();\
std::cout << "Avg time during warm-up: " << warmup_time << std::endl;\
sum = std::chrono::high_resolution_clock::duration::zero();\
for (size_t samples = 0; samples < NUM_RUNS_TO_AVG; ++samples) {\
  auto start = std::chrono::high_resolution_clock::now();\
  for (size_t i = 0; i < loop_iterations_per_run; ++i) {\
    CODE_TO_BENCHMARK\
  }\
  auto end = std::chrono::high_resolution_clock::now();\
  sum += (end - start);\
}\
auto result = std::chrono::duration_cast<TIME_UNITS>(sum / NUM_RUNS_TO_AVG).count();

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

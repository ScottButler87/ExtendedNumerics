//
// Created by scott on 10/25/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

#define LOOPS_PER_RUN (1u << 25u)
#define WARM_UP_RUNS 20
#define TOTAL_RUNS_TO_AVERAGE 80
#define OPERATION +
#define TIME_UNITS std::chrono::nanoseconds
#define TIME_UNIT_ABBREVIATION "ns"
#define OPTIMIZATION_FLAGS \
"O3"



#define BENCHMARK_CODE(CODE_TO_BENCHMARK)\
auto sum = std::chrono::high_resolution_clock::duration::zero();\
for (size_t warmups = 0; warmups < WARM_UP_RUNS; ++warmups) {\
  auto start = std::chrono::high_resolution_clock::now();\
  for (size_t i = 0; i < LOOPS_PER_RUN; ++i) {\
    CODE_TO_BENCHMARK\
  }\
  auto end = std::chrono::high_resolution_clock::now();\
  sum += (end - start);\
}\
auto warmup_time = static_cast<double>(std::chrono::duration_cast<TIME_UNITS>(sum).count() / WARM_UP_RUNS) / LOOPS_PER_RUN;\
sum = std::chrono::high_resolution_clock::duration::zero();\
for (size_t samples = 0; samples < TOTAL_RUNS_TO_AVERAGE; ++samples) {\
  auto start = std::chrono::high_resolution_clock::now();\
  for (size_t i = 0; i < LOOPS_PER_RUN; ++i) {\
    CODE_TO_BENCHMARK\
  }\
  auto end = std::chrono::high_resolution_clock::now();\
  sum += (end - start);\
}\
auto result = static_cast<double>(std::chrono::duration_cast<TIME_UNITS>(sum).count() / TOTAL_RUNS_TO_AVERAGE) / LOOPS_PER_RUN;

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_SETTINGS_AND_DEFS_HPP_

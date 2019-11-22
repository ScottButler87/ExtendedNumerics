#include <chrono>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include "../src/ExtendedNumerics.hpp"
#define TIME_UNITS nanoseconds
#define FINAL_UNITS nanoseconds
#define SAMPLES 500
#define FAST_OP_LOOPS_PER_SAMPLE 100000000
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

std::random_device dev;
std::mt19937_64 PRNG(dev());

int_fast64_t addition_no_fixnum_overflow_left = std::abs(static_cast<int_fast64_t>(PRNG() % (MAX_FIXNUM_VALUE / 2)));
int_fast64_t addition_no_fixnum_overflow_right = std::abs(static_cast<int_fast64_t>(PRNG() % (MAX_FIXNUM_VALUE / 2)));
int_fast64_t addition_no_fixnum_overflow_result = addition_no_fixnum_overflow_left + addition_no_fixnum_overflow_right;
bool hack_assert0 = (assert(addition_no_fixnum_overflow_result <= MAX_FIXNUM_VALUE), true);

int_fast64_t subtraction_no_fixnum_overflow_left = -1 * std::abs(static_cast<int_fast64_t>(PRNG() % (MAX_FIXNUM_VALUE / 2)));
int_fast64_t subtraction_no_fixnum_overflow_right = std::abs(static_cast<int_fast64_t>(PRNG() % (MAX_FIXNUM_VALUE / 2)));
int_fast64_t subtraction_no_fixnum_overflow_result = subtraction_no_fixnum_overflow_left - subtraction_no_fixnum_overflow_right;
bool hack_assert1 = (assert(subtraction_no_fixnum_overflow_result >= MIN_FIXNUM_VALUE), true);

int_fast64_t multiplication_no_fixnum_overflow_left = static_cast<int_fast64_t>(PRNG() % (static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) - 1)) + 1;
int_fast64_t multiplication_no_fixnum_overflow_right = static_cast<int_fast64_t>(PRNG() % (static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) - 1)) + 1;
bool hack_assert10 = (assert(std::sqrt(MAX_FIXNUM_VALUE) > multiplication_no_fixnum_overflow_left
    && std::sqrt(MAX_FIXNUM_VALUE) > multiplication_no_fixnum_overflow_right), true);


int_fast64_t multiplication_fixnum_overflow_left = static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) + 1 +
    (PRNG() % 1000);
int_fast64_t multiplication_fixnum_overflow_right = static_cast<int_fast64_t>(std::sqrt(MAX_FIXNUM_VALUE)) + 1 +
    (PRNG() % 1000);
bool hack_assert01 = (assert(std::sqrt(MAX_FIXNUM_VALUE) < multiplication_fixnum_overflow_left
                                 && std::sqrt(MAX_FIXNUM_VALUE) < multiplication_fixnum_overflow_right), true);

int_fast64_t overflow_range = MAX_FIXNUM_VALUE / 3;
int_fast64_t addition_fixnum_overflow_left = (MAX_FIXNUM_VALUE / 3 * 2) + std::abs(static_cast<int_fast64_t>(PRNG() % overflow_range));
int_fast64_t addition_fixnum_overflow_right = overflow_range + std::abs(static_cast<int_fast64_t>(PRNG() % overflow_range));
int_fast64_t addition_fixnum_overflow_result = addition_fixnum_overflow_left + addition_fixnum_overflow_right;
bool hack_assert2 = (assert(addition_fixnum_overflow_result > MAX_FIXNUM_VALUE), true);

int_fast64_t subtraction_fixnum_overflow_left = -1 * addition_fixnum_overflow_left;
int_fast64_t subtraction_fixnum_overflow_right = addition_fixnum_overflow_right;
int_fast64_t subtraction_fixnum_overflow_result = subtraction_fixnum_overflow_left - subtraction_fixnum_overflow_right;
bool hack_assert3 = (assert(subtraction_fixnum_overflow_result < MIN_FIXNUM_VALUE), true);

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

int main() {
  std::cout << "Minimum number of samples averaged: " << SAMPLES << std::endl << std::endl;
  std::cout << "Loop repeats per simple operation: " << FAST_OP_LOOPS_PER_SAMPLE << std::endl << std::endl;
  std::cout << "Loop repeats per extended operation: " << SLOW_OP_LOOPS_PER_SAMPLE << std::endl << std::endl;

  #define INT64_T_BENCHMARK_CALCULATION (result *= multiplication_no_fixnum_overflow_left * multiplication_no_fixnum_overflow_right)
  {
    std::cout << "Warming up calculation: " << XSTR(INT64_T_BENCHMARK_CALCULATION) << std::endl;
    TIME_BENCHMARK_OPERATION(LOOP_REPEAT_FAST_OP(INT64_T_BENCHMARK_CALCULATION))
    std::cout << "Each calculation took "
              << static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(avg_time).count()) / FAST_OP_LOOPS_PER_SAMPLE / 2
              << " " << XSTR(FINAL_UNITS) << std::endl << std::endl;
  }

  #define NUMERIC_FIXNUM_BENCHMARK_CALCULATION (a * b)
  #define DESCRIBE_NUMERIC_FIXNUM_BENCHMARK_CALCULATION ((Numeric)multiplication_no_fixnum_overflow_left * (Numeric)multiplication_no_fixnum_overflow_right)
  {
    std::cout << "Warming up calculation: " << XSTR(DESCRIBE_NUMERIC_FIXNUM_BENCHMARK_CALCULATION) << std::endl;
    Numeric a(multiplication_no_fixnum_overflow_left);
    Numeric b(multiplication_no_fixnum_overflow_right);

    TIME_BENCHMARK_OPERATION(LOOP_REPEAT_FAST_OP(NUMERIC_FIXNUM_BENCHMARK_CALCULATION))
    std::cout << "Each calculation took "
              << static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(avg_time).count()) / FAST_OP_LOOPS_PER_SAMPLE
              << " " << XSTR(FINAL_UNITS) << std::endl << std::endl;
  }

  #define NUMERIC_BIGNUM_BENCHMARK_CALCULATION (a * b)
  #define DESCRIBE_NUMERIC_BIGNUM_BENCHMARK_CALCULATION ((Numeric)multiplication_fixnum_overflow_left * (Numeric)multiplication_fixnum_overflow_right)
  {
    std::cout << "Warming up calculation: " << XSTR(DESCRIBE_NUMERIC_BIGNUM_BENCHMARK_CALCULATION) << std::endl;
    Numeric a(multiplication_fixnum_overflow_left);
    Numeric b(multiplication_fixnum_overflow_right);

    TIME_BENCHMARK_OPERATION(LOOP_REPEAT_SLOW_OP(NUMERIC_BIGNUM_BENCHMARK_CALCULATION))
    std::cout << "Each calculation took "
              << static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(avg_time).count()) / SLOW_OP_LOOPS_PER_SAMPLE
              << " " << XSTR(FINAL_UNITS) << std::endl << std::endl;
  }

  return 0;
}
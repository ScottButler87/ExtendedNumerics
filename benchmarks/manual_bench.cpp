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
#define ITERATIONS 500
#define FAST_OP_LOOPS_PER_ITERATION 100000
#define XSTR(TO_STRINGIFY) STR(TO_STRINGIFY)
#define STR(TO_STRINGIFY) #TO_STRINGIFY

#define LOOP_REPEAT_FAST_OP(OP)\
for (int i = 0; i < FAST_OP_LOOPS_PER_ITERATION; ++i) {\
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
static int_fast64_t result;
static Numeric result2(static_cast<int64_t>(0));

#define TIME_CALCULATION(CALCULATION)\
  auto previous_time =\
      std::chrono::duration_cast<std::chrono::nanoseconds>(\
        std::chrono::nanoseconds(1000));\
  auto threshold = 1e-12;\
  auto ratio = 2.0;\
  auto count = 0;\
  while (count < 10000 || abs(ratio - 1) > threshold) {\
    auto start = std::chrono::high_resolution_clock::now();\
    CALCULATION\
    auto end = std::chrono::high_resolution_clock::now();\
    auto current_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);\
    ratio = (static_cast<double>(previous_time.count()) / current_time.count());\
    do_not_optimize += result;\
    previous_time = current_time;\
    count++;\
  }\
  auto time_sum =\
      std::chrono::duration_cast<std::chrono::TIME_UNITS>(std::chrono::high_resolution_clock::duration::zero());\
  for (size_t h = 0; h < ITERATIONS; ++h) {\
    auto start = std::chrono::high_resolution_clock::now();\
    CALCULATION\
    auto end = std::chrono::high_resolution_clock::now();\
    do_not_optimize += result;\
    time_sum += std::chrono::duration_cast<std::chrono::TIME_UNITS>(end - start);\
  }\
  auto avg_time = time_sum / ITERATIONS;

int main() {
  std::cout << "Number of calculations: " << 1 << std::endl;
  std::cout << "Minimum number of iterations run: " << ITERATIONS << std::endl << std::endl;

  #define INT64_T_BENCHMARK_CALCULATION (result *= multiplication_no_fixnum_overflow_left * multiplication_no_fixnum_overflow_right)
  {
    std::cout << "Warming up calculation: " << XSTR(INT64_T_BENCHMARK_CALCULATION) << std::endl;
    TIME_CALCULATION(LOOP_REPEAT_FAST_OP(INT64_T_BENCHMARK_CALCULATION))
    std::cout << "time_sum: " << time_sum.count() << std::endl;
    std::cout << "Each calculation took "
              << static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(avg_time).count()) / FAST_OP_LOOPS_PER_ITERATION
              << " " << XSTR(FINAL_UNITS) << std::endl << std::endl;
  }

  #define NUMERIC_FIXNUM_BENCHMARK_CALCULATION (result2 = result2 * (a * b))
  {
    std::cout << "Warming up calculation: " << XSTR(NUMERIC_FIXNUM_BENCHMARK_CALCULATION) << std::endl;
    Numeric a(multiplication_no_fixnum_overflow_left);
    Numeric b(multiplication_no_fixnum_overflow_right);

    TIME_CALCULATION(LOOP_REPEAT_FAST_OP(NUMERIC_FIXNUM_BENCHMARK_CALCULATION))
    std::cout << "Each calculation took "
              << static_cast<double>(std::chrono::duration_cast<std::chrono::FINAL_UNITS>(avg_time).count()) / FAST_OP_LOOPS_PER_ITERATION
              << " " << XSTR(FINAL_UNITS) << std::endl << std::endl;
  }

  return 0;
}
#include <benchmark/benchmark.h>
#include "../src/ExtendedNumerics.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

#define BENCHMARK_WITH_MODIFIERS(name) BENCHMARK(name)->Repetitions(5)->ReportAggregatesOnly(true)

#define REP2(LINE)\
LINE LINE

#define REP4(LINE)\
REP2(LINE) REP2(LINE)

#define REPEAT_AS_NECESSARY(LINE)\
LINE


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

int_fast64_t overflow_range = MAX_FIXNUM_VALUE / 3;
int_fast64_t addition_fixnum_overflow_left = (MAX_FIXNUM_VALUE / 3 * 2) + std::abs(static_cast<int_fast64_t>(PRNG() % overflow_range));
int_fast64_t addition_fixnum_overflow_right = overflow_range + std::abs(static_cast<int_fast64_t>(PRNG() % overflow_range));
int_fast64_t addition_fixnum_overflow_result = addition_fixnum_overflow_left + addition_fixnum_overflow_right;
bool hack_assert2 = (assert(addition_fixnum_overflow_result > MAX_FIXNUM_VALUE), true);

int_fast64_t subtraction_fixnum_overflow_left = -1 * addition_fixnum_overflow_left;
int_fast64_t subtraction_fixnum_overflow_right = addition_fixnum_overflow_right;
int_fast64_t subtraction_fixnum_overflow_result = subtraction_fixnum_overflow_left - subtraction_fixnum_overflow_right;
bool hack_assert3 = (assert(subtraction_fixnum_overflow_result < MIN_FIXNUM_VALUE), true);

static void BM_LoopOverhead(benchmark::State &state) {
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(addition_no_fixnum_overflow_result);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_LoopOverhead);

static void BM_int64_t_addition(benchmark::State &state) {
  int64_t a = addition_no_fixnum_overflow_left;
  int64_t b = addition_no_fixnum_overflow_right;
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(a + b);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_int64_t_addition);

static void BM_numeric_fixnum_addition(benchmark::State &state) {
  Numeric a(std::to_string(addition_no_fixnum_overflow_left));
  Numeric b(std::to_string(addition_no_fixnum_overflow_right));
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(a + b);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_numeric_fixnum_addition);

static void BM_numeric_fixnum_addition_with_bignum_result(benchmark::State &state) {
  Numeric a(addition_fixnum_overflow_left);
  Numeric b(addition_fixnum_overflow_right);
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(a + b);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_numeric_fixnum_addition_with_bignum_result);

static void BM_int64_t_subtraction(benchmark::State &state) {
  int64_t a = subtraction_no_fixnum_overflow_left;
  int64_t b = subtraction_no_fixnum_overflow_right;
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(a - b);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_int64_t_subtraction);

static void BM_numeric_fixnum_subtraction(benchmark::State &state) {
  Numeric a(std::to_string(subtraction_no_fixnum_overflow_left));
  Numeric b(std::to_string(subtraction_no_fixnum_overflow_right));
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(a - b);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_numeric_fixnum_subtraction);

static void BM_numeric_fixnum_subtraction_with_bignum_result(benchmark::State &state) {
  Numeric a(subtraction_fixnum_overflow_left);
  Numeric b(subtraction_fixnum_overflow_right);
  for (auto _ : state) {
    REPEAT_AS_NECESSARY(benchmark::DoNotOptimize(a - b);)
  }
}
BENCHMARK_WITH_MODIFIERS(BM_numeric_fixnum_subtraction_with_bignum_result);

BENCHMARK_MAIN();
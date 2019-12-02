//
// Created by scott on 11/29/19.
//

#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_RANDOM_NUMERIC_GENERATORS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_RANDOM_NUMERIC_GENERATORS_HPP_

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/random.hpp>
#include <random>
#include "../src/ExtendedNumerics.hpp"
#include "benchmark_settings_and_defs.hpp"

struct operands {
  Numeric left;
  Numeric right;
};

std::random_device dev;
std::mt19937_64 PRNG(dev());
std::uniform_real_distribution<double> random_probability(0, 1);
std::uniform_real_distribution<double>
    random_double(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
boost::random::uniform_int_distribution<int_fast64_t> random_fixnum_internal(MIN_FIXNUM_VALUE, MAX_FIXNUM_VALUE);

FORCE_INLINE cpp_int random_cpp_int(int bit_length) {
  cpp_int &&range = cpp_int(1) << bit_length;
  boost::random::uniform_int_distribution<cpp_int> dist(-range, range);
  return dist(PRNG);
}

FORCE_INLINE Numeric random_fixnum(int bit_length) {
  assert(bit_length < 62);
  if (bit_length < 62) {
    boost::random::uniform_int_distribution<int_fast64_t> random_in_range(-(1 << bit_length), 1 << bit_length);
  } else {
    return Numeric(random_fixnum_internal(PRNG));
  }
}

FORCE_INLINE Numeric random_bignum(int bit_length) {
  return Numeric(random_cpp_int(bit_length));
}

FORCE_INLINE cpp_rational random_cpp_rational(int minimum_bit_length) {
  cpp_int &&range = cpp_int(1) << minimum_bit_length;
  cpp_int &&range_top = range << 32;
  boost::random::uniform_int_distribution<cpp_int> dist(range, range << 32);
  cpp_int numerator(dist(PRNG));
  // ensure bit length
  cpp_rational candidate(numerator, dist(PRNG));
  while (msb( boost::multiprecision::numerator(candidate)) < minimum_bit_length ) {
    candidate = cpp_rational(numerator, dist(PRNG));
  }
  if (random_probability(PRNG) > 0.50) {
    candidate = -candidate;
  }
}

FORCE_INLINE Numeric random_ratnum(int minimum_bit_length) {
  return Numeric(random_cpp_rational(minimum_bit_length));
}

FORCE_INLINE Numeric random_exact_integer_complexnum(int bit_length) {
  return Numeric(random_cpp_int(bit_length), random_cpp_int(bit_length));
}

FORCE_INLINE Numeric random_exact_rational_complexnum(int bit_length) {
  cpp_int &&range = cpp_int(1) << bit_length;
  boost::random::uniform_int_distribution<cpp_int> dist(-range, range);
  return Numeric(dist(PRNG));
}

FORCE_INLINE Numeric random_inexact_complexnum() {
  return Numeric(random_double(PRNG), random_double(PRNG));
}






#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_RANDOM_NUMERIC_GENERATORS_HPP_

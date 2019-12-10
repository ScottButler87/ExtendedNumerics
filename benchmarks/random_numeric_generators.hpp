#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_RANDOM_NUMERIC_GENERATORS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_RANDOM_NUMERIC_GENERATORS_HPP_

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
std::mt19937_64 PRNG(RANDOM_SEED_NUMBER);
//std::mt19937_64 PRNG(9439832);
std::uniform_real_distribution<double> random_probability(0, 1);
std::uniform_real_distribution<double>
    random_double(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
boost::random::uniform_int_distribution<int_fast64_t> random_fixnum_internal(0, MAX_FIXNUM_VALUE);

FORCE_INLINE cpp_int random_cpp_int(int bit_length) {
  cpp_int range = cpp_int(1) << bit_length;
  boost::random::uniform_int_distribution<cpp_int> dist(-range, range);
  return dist(PRNG);
}

FORCE_INLINE Numeric random_fixnum(int bit_length) {
  int negative = random_double(PRNG) > 0.5 ? -1 : 1;

  if (bit_length < 62) {
    boost::random::uniform_int_distribution<int_fast64_t> random_in_range(1, 1 << bit_length);
    return Numeric(negative * random_in_range(PRNG));
  } else {
    return Numeric(negative * random_fixnum_internal(PRNG));
  }
}

FORCE_INLINE Numeric random_bignum(int bit_length) {
  return Numeric(random_cpp_int(bit_length));
}

FORCE_INLINE cpp_rational random_cpp_rational(int minimum_bit_length) {
  cpp_int range_bottom = cpp_int(1) << minimum_bit_length;
  cpp_int range_top = range_bottom << 2;
  boost::random::uniform_int_distribution<cpp_int> dist(range_bottom, range_top);
  cpp_int numerator(dist(PRNG));
  cpp_int denominator(dist(PRNG));
  cpp_rational candidate(numerator, denominator);
  while (boost::multiprecision::denominator(candidate) != denominator) {
    denominator = dist(PRNG);
    candidate = cpp_rational(numerator, denominator);
  }
  return candidate;
}

FORCE_INLINE Numeric random_ratnum(int minimum_bit_length) {
  return Numeric(random_cpp_rational(minimum_bit_length));
}

FORCE_INLINE Numeric random_exact_complexnum(int bit_length) {
  return Numeric(random_cpp_int(bit_length), random_cpp_int(bit_length));
}

// May be useful if optimization is ever implemented to distinguish between types of exact complexnums
//FORCE_INLINE Numeric random_exact_rational_complexnum(int bit_length) {
//  return Numeric(random_cpp_rational(bit_length), random_cpp_rational(bit_length));
//}

FORCE_INLINE Numeric random_inexact_complexnum(int bit_length) {
  if (bit_length != 0) {
    throw std::invalid_argument("Expected 0 bit length argument for random_inexact_complexnum, "
                                "cannot specify floating point primitive bit lengths");
  }
  return Numeric(random_double(PRNG), random_double(PRNG));
}






#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_RANDOM_NUMERIC_GENERATORS_HPP_

//
// Created by scott on 10/19/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_
#define WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_

#ifndef SWIGGING_EXTENSION
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE
#endif

#include <string>
#include <cctype>

FORCE_INLINE std::string max_positive_fixnum_string() noexcept {
  static std::string max_pos_fixnum_string("4611686018427387903");
  return max_pos_fixnum_string;
}

FORCE_INLINE std::string max_negative_fixnum_string() noexcept {
  static std::string max_neg_fixnum_string("-4611686018427387904");
  return max_neg_fixnum_string;
}

static std::string MAX_POSITIVE_FIXNUM_STRING = max_positive_fixnum_string();
static std::string MAX_NEGATIVE_FIXNUM_STRING = max_negative_fixnum_string();

// https://stackoverflow.com/a/11398748/6468433
static const int tab64[64] = {
    63,  0, 58,  1, 59, 47, 53,  2,
    60, 39, 48, 27, 54, 33, 42,  3,
    61, 51, 37, 40, 49, 18, 28, 20,
    55, 30, 34, 11, 43, 14, 22,  4,
    62, 57, 46, 52, 38, 26, 32, 41,
    50, 36, 17, 19, 29, 10, 13, 21,
    56, 45, 25, 31, 35, 16,  9, 12,
    44, 24, 15,  8, 23,  7,  6,  5
};

FORCE_INLINE int log2_64 (uint64_t value)
{
  value |= value >> 1u;
  value |= value >> 2u;
  value |= value >> 4u;
  value |= value >> 8u;
  value |= value >> 16u;
  value |= value >> 32u;
  return tab64[((uint64_t)((value - (value >> 1u))*0x07EDD5E59A4E28C2)) >> 58u];
}

inline bool numeric_string_fits_in_signed_fixnum(const std::string &str) {
  size_t str_size = str.size();
  std::string *to_compare_with;
  bool first_is_zero = str[0] == '0';
  bool first_is_neg_sign = str[0] == '-';
  if (str_size == 1) {
    if (first_is_neg_sign) { throw std::invalid_argument("Can't initialize numeric from '-'"); }
    if (first_is_zero) { return true; }
  }
  if (first_is_zero || (first_is_neg_sign && str[1] == '0')) {
    throw std::invalid_argument("Fixnums cannot be initialized with leading 0s");
  } else if (str_size < 19) { return true; }
  else if (str_size > 20) { return false; }
  else if (str[0] == '-') {
    if (str_size == 19) { return true; }
    to_compare_with = &MAX_NEGATIVE_FIXNUM_STRING;
  } else {
    if (str_size == 20) { return false; }
    to_compare_with = &MAX_POSITIVE_FIXNUM_STRING;
  }
  std::string &to_cmp = *to_compare_with;
  for (size_t i = 0; i < str_size; ++i) {
    if (str[i] < to_cmp[i]) { return true; }
    else if (str[i] > to_cmp[i]) { return false; }
  }
  return true;
}

#endif //WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_

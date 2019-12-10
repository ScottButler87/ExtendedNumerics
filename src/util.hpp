#ifndef WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_
#define WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_

#ifndef FORCE_INLINE
#ifndef SWIGGING_EXTENSION
  #define FORCE_INLINE __attribute__((always_inline)) inline
#else
  #define FORCE_INLINE
#endif
#endif

#include <string>
#include <cctype>
#include <cstdint>

#define MAX_FIXNUM_VALUE 4611686018427387903
#define MIN_FIXNUM_VALUE -4611686018427387904

#define u64(c) (static_cast<uint64_t>(c))
#define i64(c) (static_cast<int64_t>(c))

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

FORCE_INLINE bool added_without_fixnum_overflow(int64_t left, int64_t right, int64_t &result) {
  if ((right > 0) && (left > (MAX_FIXNUM_VALUE - right))) { return false; }
  if ((right < 0) && (left < (MIN_FIXNUM_VALUE - right))) { return false; }
  result = left + right;
  return true;
}

FORCE_INLINE bool subtracted_without_fixnum_overflow(int64_t left, int64_t right, int64_t &result) {
  if ((right > 0) && (left < (MIN_FIXNUM_VALUE + right))) { return false; }
  if ((right < 0) && (left > (MAX_FIXNUM_VALUE + right))) { return false; }
  result = left - right;
  return true;
}

FORCE_INLINE bool multiplied_without_fixnum_overflow(int64_t left, int64_t right, int64_t &result) {
  if (left > (MAX_FIXNUM_VALUE / right)) { return false; }
  if (left < (MIN_FIXNUM_VALUE / right)) { return false; }
  result = left * right;
  return MAX_FIXNUM_VALUE >= result; // check for -1 * MIN_FIXNUM_VALUE
}

FORCE_INLINE bool divided_without_fixnum_overflow_or_precision_loss(int64_t left, int64_t right, int64_t &result) {
  if ((right == -1) && (left == MIN_FIXNUM_VALUE)) { return false; }
  if ((left % right) != 0) { return false; }
  result = left / right;
  return true;
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

//
// Created by scott on 10/19/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_
#define WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_

#include <string>

inline bool numeric_string_fits_in_signed_fixnum(const std::string &str) {
  static std::string MAX_POSITIVE_FIXNUM_STRING("4611686018427387903");
  static std::string MAX_NEGATIVE_FIXNUM_STRING("-4611686018427387904");

  size_t str_size = str.size();
  std::string *to_compare_with;

  if (str_size < 19) { return true; }
  else if (str_size > 20) { return false; }
  else if (str[0] == '-') {
    if (str_size == 19) { return true; }
    to_compare_with = &MAX_NEGATIVE_FIXNUM_STRING;
  } else {
    if (str_size == 20) { return false; }
    to_compare_with = &MAX_POSITIVE_FIXNUM_STRING;
  }
  for (size_t i = 0; i < str_size; ++i) {
    if (str[i] > (*to_compare_with)[i] && str[i] != 0) { return false; }
  }

  return true;
}

#endif //WASMEXTENDEDNUMERICS_SRC_UTIL_HPP_

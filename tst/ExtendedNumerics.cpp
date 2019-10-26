//
// Created by scott on 10/14/19.
//

#include <gtest/gtest.h>
#include "../src/ExtendedNumerics.hpp"

static std::string POSITIVE_MAX_FIXNUM = "4611686018427387903";
static std::string POSITIVE_ONE_TOO_LARGE = "4611686018427387904";
static std::string POSITIVE_ONE_DIGIT_TOO_LARGE = "10000000000000000000";
static std::string POSITIVE_FIXNUM = "1234567890";

static std::string NEGATIVE_MAX_FIXNUM = "-4611686018427387904";
static std::string NEGATIVE_ONE_TOO_LARGE = "-4611686018427387905";
static std::string NEGATIVE_ONE_DIGIT_TOO_LARGE = "-10000000000000000000";
static std::string NEGATIVE_FIXNUM = "-1234567890";

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, ZeroAccepted) {
  assert(numeric_string_fits_in_signed_fixnum("0"));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, OneAccepted) {
  assert(numeric_string_fits_in_signed_fixnum("1"));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, NegativeOneAccepted) {
  assert(numeric_string_fits_in_signed_fixnum("-1"));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, PositiveFixnumAccepted) {
  assert(numeric_string_fits_in_signed_fixnum(POSITIVE_FIXNUM));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, NegativeFixnumAccepted) {
  assert(numeric_string_fits_in_signed_fixnum(NEGATIVE_FIXNUM));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, PositiveMaxAccepted) {
  assert(numeric_string_fits_in_signed_fixnum(POSITIVE_MAX_FIXNUM));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, NegativeMaxAccepted) {
  assert(numeric_string_fits_in_signed_fixnum(NEGATIVE_MAX_FIXNUM));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, PositiveOneTooLargeRejected) {
  assert(!numeric_string_fits_in_signed_fixnum(POSITIVE_ONE_TOO_LARGE));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, PositiveOneDigitTooLargeRejected) {
  assert(!numeric_string_fits_in_signed_fixnum(POSITIVE_ONE_DIGIT_TOO_LARGE));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, NegativeOneTooLargeRejected) {
  assert(!numeric_string_fits_in_signed_fixnum(NEGATIVE_ONE_TOO_LARGE));
}

TEST(ExtendedNumerics_Helper_numeric_string_fits_in_signed_fixnum, NegativeOneDigitTooLargeRejected) {
  assert(!numeric_string_fits_in_signed_fixnum(NEGATIVE_ONE_DIGIT_TOO_LARGE));
}

TEST(ExtendedNumerics_Fixnum, NegativeFixnumRemainsNegative) {
  Numeric negative_one_fixnum(-1);
  Numeric positive_one_fixnum(1);
  Numeric zero_fixnum(static_cast<int64_t>(0));
  assert(zero_fixnum == (negative_one_fixnum + positive_one_fixnum));

  Numeric negative_twelve_fixnum(-12);
  Numeric positive_seven_fixnum(7);
  Numeric negative_five_fixnum(-5);
  assert(negative_five_fixnum == (negative_twelve_fixnum + positive_seven_fixnum));
//  assert(left == (left * right));
}

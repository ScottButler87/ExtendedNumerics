// Copyright 2019 Scott Butler
#include "../src/ExtendedNumerics.hpp"
#include <gtest/gtest.h>

#define SYMMETRIC_OP_TEST(SUITE_NAME, TEST_NAME, OP, LEFT, RIGHT, EXPECTED)\
TEST(SUITE_NAME, TEST_NAME) {\
  auto result = LEFT OP RIGHT;\
  auto symmetric_result = RIGHT OP LEFT;\
  ASSERT_EQ(*result, EXPECTED);\
  ASSERT_EQ(*symmetric_result, EXPECTED);\
}

/**
 * Values often used in tests
 */

//static ExactNum default_zero;
//static ExactNum pos_zero(default_zero, false);
//static ExactNum neg_zero(default_zero, true);
//static ExactNum pos_one(1u, false);
//static ExactNum neg_one(1u, true);

/**
 * Constructor Tests
 */

TEST(ExactNumCtorTest, DefaultCtorMakesPositiveZero) {
  ExactNum zero_default;
  ExactNum bignum_zero(std::make_unique<const Bignum>(0u, false));
  ExactNum ratnum_zero(std::make_unique<const Ratnum>(0u, 1u, false));

  ExactNum c = zero_default + zero_default;
  std::cout << sizeof(c) <<  ", " << sizeof(bignum_zero) << ", " << sizeof(ratnum_zero);
}
//
/////**
//// * Addition Tests
//// */
//
//TEST(ExactNumAdditionTest, ZeroPlusZero) {
//  ExactNum zero;
//  ExactNum zero2;
//  auto sum = zero + zero2;
//  ASSERT_EQ(*sum, zero);
//}
//
//TEST(ExactNumAdditionTest, NegativeZeroPlusNegativeZero) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum negative_zero2(zero, true);
//  auto sum = negative_zero + negative_zero2;
//  ASSERT_EQ(*sum, negative_zero);
//}
//
//TEST(ExactNumAdditionTest, ZeroPlusOne) {
//  ExactNum zero;
//  ExactNum one(1u, false);
//  auto sum = zero + one;
//  auto sum2 = one + zero;
//  ASSERT_EQ(*sum, one);
//  ASSERT_EQ(*sum2, one);
//}
//
//TEST(ExactNumAdditionTest, ZeroPlusNegativeOne) {
//  ExactNum zero;
//  ExactNum negative_one(1u, true);
//  auto sum = zero + negative_one;
//  auto sum2 = negative_one + zero;
//  ASSERT_EQ(*sum, negative_one);
//  ASSERT_EQ(*sum2, negative_one);
//}
//
//TEST(ExactNumAdditionTest, NegativeZeroPlusOne) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum one(1u, false);
//  auto sum = negative_zero + one;
//  auto sum2 = one + negative_zero;
//  ASSERT_EQ(*sum, one);
//  ASSERT_EQ(*sum2, one);
//}
//
//TEST(ExactNumAdditionTest, NegativeZeroPlusNegativeOne) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum negative_one(1u, true);
//  auto sum = negative_zero + negative_one;
//  auto sum2 = negative_one + negative_zero;
//  ASSERT_EQ(*sum, negative_one);
//  ASSERT_EQ(*sum2, negative_one);
//}
//
//TEST(ExactNumAdditionTest, OnePlusNegativeOneIsZero) {
//  ExactNum zero;
//  ExactNum negative_one(1u, true);
//  ExactNum one(1u, false);
//  auto sum = negative_one + one;
//  auto sum2 = one + negative_one;
//  ASSERT_EQ(*sum, zero);
//  ASSERT_EQ(*sum2, zero);
//}
//
//TEST(ExactNumAdditionTest, DigitMaxPlusNegativeDigitMaxIsZero) {
//  ExactNum zero;
//  ExactNum negative_digit_max(UINT64_MAX, true);
//  ExactNum positive_digit_max(UINT64_MAX, false);
//  auto sum = negative_digit_max + positive_digit_max;
//  auto sum2 = positive_digit_max + negative_digit_max;
//  ASSERT_EQ(*sum, zero);
//  ASSERT_EQ(*sum2, zero);
//}

//TEST(ExactNumAdditionTest, MaxTwoDigitPlusNegativeMaxTwoDigitIsZero) {
//  ExactNum zero;
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  ExactNum negative_two_digit_max(max_two_digits, true);
//  ExactNum positive_two_digit_max(std::move(max_two_digits), false);
//  auto sum = negative_two_digit_max + positive_two_digit_max;
//  auto sum2 = positive_two_digit_max + negative_two_digit_max;
//  ASSERT_EQ(*sum, zero);
//  ASSERT_EQ(*sum2, zero);
//}
//
//TEST(ExactNumAdditionTest, MinTwoDigitPlusNegativeMinTwoDigitIsZero) {
//  ExactNum zero;
//  std::vector<uint64_t> min_two_digit{0u, 1u};
//  ExactNum negative_two_digit_min(min_two_digit, true);
//  ExactNum positive_two_digit_min(min_two_digit, false);
//  auto sum = negative_two_digit_min + positive_two_digit_min;
//  auto sum2 = positive_two_digit_min + negative_two_digit_min;
//  ASSERT_EQ(*sum, zero);
//  ASSERT_EQ(*sum2, zero);
//}
//
//TEST(ExactNumAdditionTest, MaxOneDigitPlusMaxOneDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
//  ExactNum expected(std::move(expected_digits), false);
//  ExactNum max_one_digit(UINT64_MAX, false);
//  ExactNum max_one_digit2(UINT64_MAX, false);
//  auto sum = max_one_digit + max_one_digit2;
//  auto sum2 = max_one_digit2 + max_one_digit;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}
//
//TEST(ExactNumAdditionTest, MaxTwoDigitPlusMaxTwoDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
//  ExactNum expected(std::move(expected_digits), false);
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  ExactNum max_two_digit(max_two_digits, false);
//  ExactNum max_two_digit2(std::move(max_two_digits), false);
//  auto sum = max_two_digit + max_two_digit2;
//  auto sum2 = max_two_digit2 + max_two_digit;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}
//
//TEST(ExactNumAdditionTest, AdditionCausingCarry) {
//  ExactNum zero;
//  ExactNum max_digit(UINT64_MAX, false);
//  ExactNum one(1u, false);
//  std::vector<uint64_t> expected_digits{0u, 1u};
//  ExactNum expected(expected_digits, false);
//  auto sum = max_digit + one;
//  auto sum2 = one + max_digit;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}
//
//TEST(ExactNumAdditionTest, AdditionRequiringBorrow) {
//  std::vector<uint64_t> borrowee_digits{0u, 1u};
//  ExactNum one_zero(borrowee_digits, false);
//  ExactNum negative_one(1u, true);
//  ExactNum expected(UINT64_MAX, false);
//  auto sum = one_zero + negative_one;
//  auto sum2 = negative_one + one_zero;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}

/**
 * Subtraction Tests
 */
//
//TEST(ExactNumSubtractionTest, ZeroMinusZero) {
//  ExactNum zero;
//  ExactNum zero2;
//  auto difference = zero - zero2;
//  ASSERT_EQ(*difference, zero);
//}
//
//TEST(ExactNumSubtractionTest, NegativeZeroMinusNegativeZero) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum negative_zero2(zero, true);
//  auto difference = negative_zero - negative_zero2;
//  ASSERT_EQ(*difference, negative_zero);
//}
//TEST(ExactNumSubtractionTest, ZeroMinusOne) {
//  ExactNum zero;
//  ExactNum one(1u, false);
//  ExactNum expected(1u, true);
//  auto difference = zero - one;
//  auto diff2 = ExactNum(1u, false) - ExactNum(1u, false);
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, ZeroMinusNegativeOne) {
//  ExactNum zero;
//  ExactNum negative_one(1u, true);
//  ExactNum one(1u, false);
//  auto difference = zero - negative_one;
//  ASSERT_EQ(*difference, one);
//}
//
//TEST(ExactNumAdditionTest, NegativeZeroMinusOne) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum one(1u, false);
//  ExactNum negative_one(1u, true);
//  auto difference = negative_zero - one;
//  ASSERT_EQ(*difference, negative_one);
//}
//
//TEST(ExactNumAdditionTest, OneMinusNegativeZero) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum one(1u, false);
//  auto difference = one - negative_zero;
//  ASSERT_EQ(*difference, one);
//}
//
//TEST(ExactNumAdditionTest, NegativeOneMinusNegativeZero) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum negative_one(1u, true);
//  auto difference = negative_one - negative_zero;
//  ASSERT_EQ(*difference, negative_one);
//}
//
//TEST(ExactNumAdditionTest, NegativeZeroMinusNegativeOne) {
//  ExactNum zero;
//  ExactNum negative_zero(zero, true);
//  ExactNum negative_one(1u, true);
//  ExactNum one(1u, false);
//  auto difference = negative_zero - negative_one;
//  ASSERT_EQ(*difference, one);
//}
//
//TEST(ExactNumSubtractionTest, NegativeOneMinusNegativeOne) {
//  ExactNum zero;
//  ExactNum negative_one(1u, true);
//  ExactNum negative_one2(1u, true);
//  auto difference = negative_one - negative_one2;
//  ASSERT_EQ(*difference, zero);
//}
//
//TEST(ExactNumSubtractionTest, NegativeDigitMaxMinusNegativeDigitMaxIsZero) {
//  ExactNum zero;
//  ExactNum negative_digit_max(UINT64_MAX, true);
//  ExactNum negative_digit_max2(UINT64_MAX, true);
//  auto difference = negative_digit_max - negative_digit_max2;
//  ASSERT_EQ(*difference, zero);
//}

//TEST(ExactNumSubtractionTest, NegativeMaxTwoDigitMinusNegativeMaxTwoDigitIsZero) {
//  ExactNum zero;
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  ExactNum negative_two_digit_max(max_two_digits, true);
//  ExactNum negative_two_digit_max2(std::move(max_two_digits), true);
//  auto difference = negative_two_digit_max - negative_two_digit_max2;
//  ASSERT_EQ(*difference, zero);
//}
//
//TEST(ExactNumSubtractionTest, NegativeMinTwoDigitMinusNegativeMinTwoDigitIsZero) {
//  ExactNum zero;
//  std::vector<uint64_t> min_two_digit{0u, 1u};
//  ExactNum negative_min_two_digit(min_two_digit, true);
//  ExactNum negative_min_two_digit2(std::move(min_two_digit), true);
//  auto difference = negative_min_two_digit - negative_min_two_digit2;
//  ASSERT_EQ(*difference, zero);
//}
//
//TEST(ExactNumSubtractionTest, MinTwoDigitMinusNegativeMinTwoDigit) {
//  ExactNum expected(std::vector<uint64_t>({0u, 2u}), false);
//  std::vector<uint64_t> min_two_digits{0u, 1u};
//  ExactNum min_two_digit(min_two_digits, false);
//  ExactNum negative_min_two_digit(std::move(min_two_digits), true);
//  auto difference = min_two_digit - negative_min_two_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, NegativeMaxOneDigitMinusMaxOneDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
//  ExactNum expected(std::move(expected_digits), true);
//  ExactNum negative_max_one_digit(UINT64_MAX, true);
//  ExactNum max_one_digit(UINT64_MAX, false);
//  auto difference = negative_max_one_digit - max_one_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, MaxOneDigitMinusNegativeMaxOneDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
//  ExactNum expected(std::move(expected_digits), false);
//  ExactNum negative_max_one_digit(UINT64_MAX, true);
//  ExactNum max_one_digit(UINT64_MAX, false);
//  auto difference = max_one_digit - negative_max_one_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, NegativeMaxTwoDigitMinusMaxTwoDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
//  ExactNum expected(std::move(expected_digits), true);
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  ExactNum negative_max_two_digit(max_two_digits, true);
//  ExactNum max_two_digit(std::move(max_two_digits), false);
//  auto difference = negative_max_two_digit - max_two_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, PositiveMaxTwoDigitMinusNegativeMaxTwoDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
//  ExactNum expected(std::move(expected_digits), false);
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  ExactNum max_two_digit(max_two_digits, false);
//  ExactNum negative_max_two_digit(std::move(max_two_digits), true);
//  auto difference = max_two_digit - negative_max_two_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, SubtractionCausingCarryPositive) {
//  ExactNum zero;
//  ExactNum max_digit(UINT64_MAX, false);
//  ExactNum negative_one(1u, true);
//  std::vector<uint64_t> expected_digits{0u, 1u};
//  ExactNum expected(std::move(expected_digits), false);
//  auto difference = max_digit - negative_one;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, SubtractionCausingCarryNegative) {
//  ExactNum zero;
//  ExactNum negative_max_digit(UINT64_MAX, true);
//  ExactNum one(1u, false);
//  std::vector<uint64_t> expected_digits{0u, 1u};
//  ExactNum expected(std::move(expected_digits), true);
//  auto difference = negative_max_digit - one;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, SubtractionRequiringBorrowPositive) {
//  std::vector<uint64_t> borrowee_digits{0u, 1u};
//  ExactNum one_zero(std::move(borrowee_digits), false);
//  ExactNum one(1u, false);
//  ExactNum expected(UINT64_MAX, false);
//  auto difference = one_zero - one;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(ExactNumSubtractionTest, SubtractionRequiringBorrowNegative) {
//  std::vector<uint64_t> borrowee_digits{0u, 1u};
//  ExactNum one_zero(std::move(borrowee_digits), true);
//  ExactNum one(1u, true);
//  ExactNum expected(UINT64_MAX, true);
//  auto difference = one_zero - one;
//  ASSERT_EQ(*difference, expected);
//}
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    PositiveZeroTimesPositiveZeroIsPositiveZero,
//    *, pos_zero, pos_zero,
//    pos_zero);
//
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    PositiveZeroTimesNegativeZeroIsNegativeZero,
//    *, neg_zero, pos_zero,
//    neg_zero);
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    NegativeZeroTimesNegativeZeroIsPositiveZero,
//    *, neg_zero, neg_zero,
//    pos_zero);
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    PositiveOneTimesPositiveOneIsPositiveOne,
//    *, pos_one, pos_one,
//    pos_one);
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    NegativeOneTimesNegativeOneIsPositiveOne,
//    *, neg_one, neg_one,
//    pos_one);
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    PositiveOneTimesNegativeOneIsNegativeOne,
//    *, pos_one, neg_one,
//    neg_one);
//
//SYMMETRIC_OP_TEST(
//    ExactNumMultiplicationTest,
//    PositiveOneTimesZeroIsZero,
//    *, pos_one, default_zero,
//    default_zero);
//
//TEST(ExactNumDivisionTests, ExactNumsDoNotExhibitIntegerDivision) {
//  ExactNum a(7u, false);
//  ExactNum b(8u, false);
//  ExactNum c(3u, false);
//  ExactNum expected(7u, 8u, false);
//  ExactNum expected2(7u, 3u, false);
//  auto result = a / b;
//  auto result2 = a / c;
//  ASSERT_EQ(*result, expected);
//  ASSERT_EQ(*result2, expected2);
//}


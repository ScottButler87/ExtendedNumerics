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

static Ratnum default_zero;
static Ratnum pos_zero(default_zero, false);
static Ratnum neg_zero(default_zero, true);
static Ratnum pos_one(1u, false);
static Ratnum neg_one(1u, true);

/**
 * Constructor Tests
 */

TEST(RatnumCtorTest, DefaultCtorMakesPositiveZero) {
  Ratnum zero_default;
  Ratnum zero(0u, false);
  ASSERT_EQ(zero_default, zero);
}

///**
// * Addition Tests
// */

TEST(RatnumAdditionTest, ZeroPlusZero) {
  Ratnum zero;
  Ratnum zero2;
  auto sum = zero + zero2;
  ASSERT_EQ(*sum, zero);
}

TEST(RatnumAdditionTest, NegativeZeroPlusNegativeZero) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum negative_zero2(zero, true);
  auto sum = negative_zero + negative_zero2;
  ASSERT_EQ(*sum, negative_zero);
}

TEST(RatnumAdditionTest, ZeroPlusOne) {
  Ratnum zero;
  Ratnum one(1u, false);
  auto sum = zero + one;
  auto sum2 = one + zero;
  ASSERT_EQ(*sum, one);
  ASSERT_EQ(*sum2, one);
}

TEST(RatnumAdditionTest, ZeroPlusNegativeOne) {
  Ratnum zero;
  Ratnum negative_one(1u, true);
  auto sum = zero + negative_one;
  auto sum2 = negative_one + zero;
  ASSERT_EQ(*sum, negative_one);
  ASSERT_EQ(*sum2, negative_one);
}

TEST(RatnumAdditionTest, NegativeZeroPlusOne) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum one(1u, false);
  auto sum = negative_zero + one;
  auto sum2 = one + negative_zero;
  ASSERT_EQ(*sum, one);
  ASSERT_EQ(*sum2, one);
}

TEST(RatnumAdditionTest, NegativeZeroPlusNegativeOne) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum negative_one(1u, true);
  auto sum = negative_zero + negative_one;
  auto sum2 = negative_one + negative_zero;
  ASSERT_EQ(*sum, negative_one);
  ASSERT_EQ(*sum2, negative_one);
}

TEST(RatnumAdditionTest, OnePlusNegativeOneIsZero) {
  Ratnum zero;
  Ratnum negative_one(1u, true);
  Ratnum one(1u, false);
  auto sum = negative_one + one;
  auto sum2 = one + negative_one;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

TEST(RatnumAdditionTest, DigitMaxPlusNegativeDigitMaxIsZero) {
  Ratnum zero;
  Ratnum negative_digit_max(UINT64_MAX, true);
  Ratnum positive_digit_max(UINT64_MAX, false);
  auto sum = negative_digit_max + positive_digit_max;
  auto sum2 = positive_digit_max + negative_digit_max;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

//TEST(RatnumAdditionTest, MaxTwoDigitPlusNegativeMaxTwoDigitIsZero) {
//  Ratnum zero;
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  Ratnum negative_two_digit_max(max_two_digits, true);
//  Ratnum positive_two_digit_max(std::move(max_two_digits), false);
//  auto sum = negative_two_digit_max + positive_two_digit_max;
//  auto sum2 = positive_two_digit_max + negative_two_digit_max;
//  ASSERT_EQ(*sum, zero);
//  ASSERT_EQ(*sum2, zero);
//}
//
//TEST(RatnumAdditionTest, MinTwoDigitPlusNegativeMinTwoDigitIsZero) {
//  Ratnum zero;
//  std::vector<uint64_t> min_two_digit{0u, 1u};
//  Ratnum negative_two_digit_min(min_two_digit, true);
//  Ratnum positive_two_digit_min(min_two_digit, false);
//  auto sum = negative_two_digit_min + positive_two_digit_min;
//  auto sum2 = positive_two_digit_min + negative_two_digit_min;
//  ASSERT_EQ(*sum, zero);
//  ASSERT_EQ(*sum2, zero);
//}
//
//TEST(RatnumAdditionTest, MaxOneDigitPlusMaxOneDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
//  Ratnum expected(std::move(expected_digits), false);
//  Ratnum max_one_digit(UINT64_MAX, false);
//  Ratnum max_one_digit2(UINT64_MAX, false);
//  auto sum = max_one_digit + max_one_digit2;
//  auto sum2 = max_one_digit2 + max_one_digit;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}
//
//TEST(RatnumAdditionTest, MaxTwoDigitPlusMaxTwoDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
//  Ratnum expected(std::move(expected_digits), false);
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  Ratnum max_two_digit(max_two_digits, false);
//  Ratnum max_two_digit2(std::move(max_two_digits), false);
//  auto sum = max_two_digit + max_two_digit2;
//  auto sum2 = max_two_digit2 + max_two_digit;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}
//
//TEST(RatnumAdditionTest, AdditionCausingCarry) {
//  Ratnum zero;
//  Ratnum max_digit(UINT64_MAX, false);
//  Ratnum one(1u, false);
//  std::vector<uint64_t> expected_digits{0u, 1u};
//  Ratnum expected(expected_digits, false);
//  auto sum = max_digit + one;
//  auto sum2 = one + max_digit;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}
//
//TEST(RatnumAdditionTest, AdditionRequiringBorrow) {
//  std::vector<uint64_t> borrowee_digits{0u, 1u};
//  Ratnum one_zero(borrowee_digits, false);
//  Ratnum negative_one(1u, true);
//  Ratnum expected(UINT64_MAX, false);
//  auto sum = one_zero + negative_one;
//  auto sum2 = negative_one + one_zero;
//  ASSERT_EQ(*sum, expected);
//  ASSERT_EQ(*sum2, expected);
//}

/**
 * Subtraction Tests
 */

TEST(RatnumSubtractionTest, ZeroMinusZero) {
  Ratnum zero;
  Ratnum zero2;
  auto difference = zero - zero2;
  ASSERT_EQ(*difference, zero);
}

TEST(RatnumSubtractionTest, NegativeZeroMinusNegativeZero) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum negative_zero2(zero, true);
  auto difference = negative_zero - negative_zero2;
  ASSERT_EQ(*difference, negative_zero);
}
TEST(RatnumSubtractionTest, ZeroMinusOne) {
  Ratnum zero;
  Ratnum one(1u, false);
  Ratnum expected(1u, true);
  auto difference = zero - one;
  auto diff2 = Ratnum(1u, false) - Ratnum(1u, false);
  ASSERT_EQ(*difference, expected);
}

TEST(RatnumSubtractionTest, ZeroMinusNegativeOne) {
  Ratnum zero;
  Ratnum negative_one(1u, true);
  Ratnum one(1u, false);
  auto difference = zero - negative_one;
  ASSERT_EQ(*difference, one);
}

TEST(RatnumAdditionTest, NegativeZeroMinusOne) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum one(1u, false);
  Ratnum negative_one(1u, true);
  auto difference = negative_zero - one;
  ASSERT_EQ(*difference, negative_one);
}

TEST(RatnumAdditionTest, OneMinusNegativeZero) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum one(1u, false);
  auto difference = one - negative_zero;
  ASSERT_EQ(*difference, one);
}

TEST(RatnumAdditionTest, NegativeOneMinusNegativeZero) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum negative_one(1u, true);
  auto difference = negative_one - negative_zero;
  ASSERT_EQ(*difference, negative_one);
}

TEST(RatnumAdditionTest, NegativeZeroMinusNegativeOne) {
  Ratnum zero;
  Ratnum negative_zero(zero, true);
  Ratnum negative_one(1u, true);
  Ratnum one(1u, false);
  auto difference = negative_zero - negative_one;
  ASSERT_EQ(*difference, one);
}

TEST(RatnumSubtractionTest, NegativeOneMinusNegativeOne) {
  Ratnum zero;
  Ratnum negative_one(1u, true);
  Ratnum negative_one2(1u, true);
  auto difference = negative_one - negative_one2;
  ASSERT_EQ(*difference, zero);
}

TEST(RatnumSubtractionTest, NegativeDigitMaxMinusNegativeDigitMaxIsZero) {
  Ratnum zero;
  Ratnum negative_digit_max(UINT64_MAX, true);
  Ratnum negative_digit_max2(UINT64_MAX, true);
  auto difference = negative_digit_max - negative_digit_max2;
  ASSERT_EQ(*difference, zero);
}

//TEST(RatnumSubtractionTest, NegativeMaxTwoDigitMinusNegativeMaxTwoDigitIsZero) {
//  Ratnum zero;
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  Ratnum negative_two_digit_max(max_two_digits, true);
//  Ratnum negative_two_digit_max2(std::move(max_two_digits), true);
//  auto difference = negative_two_digit_max - negative_two_digit_max2;
//  ASSERT_EQ(*difference, zero);
//}
//
//TEST(RatnumSubtractionTest, NegativeMinTwoDigitMinusNegativeMinTwoDigitIsZero) {
//  Ratnum zero;
//  std::vector<uint64_t> min_two_digit{0u, 1u};
//  Ratnum negative_min_two_digit(min_two_digit, true);
//  Ratnum negative_min_two_digit2(std::move(min_two_digit), true);
//  auto difference = negative_min_two_digit - negative_min_two_digit2;
//  ASSERT_EQ(*difference, zero);
//}
//
//TEST(RatnumSubtractionTest, MinTwoDigitMinusNegativeMinTwoDigit) {
//  Ratnum expected(std::vector<uint64_t>({0u, 2u}), false);
//  std::vector<uint64_t> min_two_digits{0u, 1u};
//  Ratnum min_two_digit(min_two_digits, false);
//  Ratnum negative_min_two_digit(std::move(min_two_digits), true);
//  auto difference = min_two_digit - negative_min_two_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, NegativeMaxOneDigitMinusMaxOneDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
//  Ratnum expected(std::move(expected_digits), true);
//  Ratnum negative_max_one_digit(UINT64_MAX, true);
//  Ratnum max_one_digit(UINT64_MAX, false);
//  auto difference = negative_max_one_digit - max_one_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, MaxOneDigitMinusNegativeMaxOneDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
//  Ratnum expected(std::move(expected_digits), false);
//  Ratnum negative_max_one_digit(UINT64_MAX, true);
//  Ratnum max_one_digit(UINT64_MAX, false);
//  auto difference = max_one_digit - negative_max_one_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, NegativeMaxTwoDigitMinusMaxTwoDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
//  Ratnum expected(std::move(expected_digits), true);
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  Ratnum negative_max_two_digit(max_two_digits, true);
//  Ratnum max_two_digit(std::move(max_two_digits), false);
//  auto difference = negative_max_two_digit - max_two_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, PositiveMaxTwoDigitMinusNegativeMaxTwoDigit) {
//  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
//  Ratnum expected(std::move(expected_digits), false);
//  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
//  Ratnum max_two_digit(max_two_digits, false);
//  Ratnum negative_max_two_digit(std::move(max_two_digits), true);
//  auto difference = max_two_digit - negative_max_two_digit;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, SubtractionCausingCarryPositive) {
//  Ratnum zero;
//  Ratnum max_digit(UINT64_MAX, false);
//  Ratnum negative_one(1u, true);
//  std::vector<uint64_t> expected_digits{0u, 1u};
//  Ratnum expected(std::move(expected_digits), false);
//  auto difference = max_digit - negative_one;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, SubtractionCausingCarryNegative) {
//  Ratnum zero;
//  Ratnum negative_max_digit(UINT64_MAX, true);
//  Ratnum one(1u, false);
//  std::vector<uint64_t> expected_digits{0u, 1u};
//  Ratnum expected(std::move(expected_digits), true);
//  auto difference = negative_max_digit - one;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, SubtractionRequiringBorrowPositive) {
//  std::vector<uint64_t> borrowee_digits{0u, 1u};
//  Ratnum one_zero(std::move(borrowee_digits), false);
//  Ratnum one(1u, false);
//  Ratnum expected(UINT64_MAX, false);
//  auto difference = one_zero - one;
//  ASSERT_EQ(*difference, expected);
//}
//
//TEST(RatnumSubtractionTest, SubtractionRequiringBorrowNegative) {
//  std::vector<uint64_t> borrowee_digits{0u, 1u};
//  Ratnum one_zero(std::move(borrowee_digits), true);
//  Ratnum one(1u, true);
//  Ratnum expected(UINT64_MAX, true);
//  auto difference = one_zero - one;
//  ASSERT_EQ(*difference, expected);
//}

SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    PositiveZeroTimesPositiveZeroIsPositiveZero,
    *, pos_zero, pos_zero,
    pos_zero);


SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    PositiveZeroTimesNegativeZeroIsNegativeZero,
    *, neg_zero, pos_zero,
    neg_zero);

SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    NegativeZeroTimesNegativeZeroIsPositiveZero,
    *, neg_zero, neg_zero,
    pos_zero);

SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    PositiveOneTimesPositiveOneIsPositiveOne,
    *, pos_one, pos_one,
    pos_one);

SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    NegativeOneTimesNegativeOneIsPositiveOne,
    *, neg_one, neg_one,
    pos_one);

SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    PositiveOneTimesNegativeOneIsNegativeOne,
    *, pos_one, neg_one,
    neg_one);

SYMMETRIC_OP_TEST(
    RatnumMultiplicationTest,
    PositiveOneTimesZeroIsZero,
    *, pos_one, default_zero,
    default_zero);

TEST(RatnumDivisionTests, RatnumsDoNotExhibitIntegerDivision) {
  Ratnum a(7u, false);
  Ratnum b(8u, false);
  Ratnum c(3u, false);
  Ratnum expected(7u, 8u, false);
  Ratnum expected2(7u, 3u, false);
  auto result = a / b;
  auto result2 = a / c;
  ASSERT_EQ(*result, expected);
  ASSERT_EQ(*result2, expected2);
}


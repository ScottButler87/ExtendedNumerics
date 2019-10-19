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

static Bignum default_zero;
static Bignum pos_zero(default_zero, false);
static Bignum neg_zero(default_zero, true);
static Bignum pos_one(1u, false);
static Bignum neg_one(1u, true);

/**
 * Constructor Tests
 */

TEST(BignumCtorTest, DefaultCtorMakesPositiveZero) {
  Bignum zero_default;
  Bignum zero(0u, false);
  std::cout << sizeof(char) << std::endl;
  ASSERT_EQ(zero_default, zero);
}

///**
// * Addition Tests
// */

TEST(BignumAdditionTest, ZeroPlusZero) {
  Bignum zero;
  Bignum zero2;
  auto sum = zero + zero2;
  ASSERT_EQ(*sum, zero);
}

TEST(BignumAdditionTest, NegativeZeroPlusNegativeZero) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum negative_zero2(zero, true);
  auto sum = negative_zero + negative_zero2;
  ASSERT_EQ(*sum, negative_zero);
}

TEST(BignumAdditionTest, ZeroPlusOne) {
  Bignum zero;
  Bignum one(1u, false);
  auto sum = zero + one;
  auto sum2 = one + zero;
  ASSERT_EQ(*sum, one);
  ASSERT_EQ(*sum2, one);
}

TEST(BignumAdditionTest, ZeroPlusNegativeOne) {
  Bignum zero;
  Bignum negative_one(1u, true);
  auto sum = zero + negative_one;
  auto sum2 = negative_one + zero;
  ASSERT_EQ(*sum, negative_one);
  ASSERT_EQ(*sum2, negative_one);
}

TEST(BignumAdditionTest, NegativeZeroPlusOne) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum one(1u, false);
  auto sum = negative_zero + one;
  auto sum2 = one + negative_zero;
  ASSERT_EQ(*sum, one);
  ASSERT_EQ(*sum2, one);
}

TEST(BignumAdditionTest, NegativeZeroPlusNegativeOne) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum negative_one(1u, true);
  auto sum = negative_zero + negative_one;
  auto sum2 = negative_one + negative_zero;
  ASSERT_EQ(*sum, negative_one);
  ASSERT_EQ(*sum2, negative_one);
}

TEST(BignumAdditionTest, OnePlusNegativeOneIsZero) {
  Bignum zero;
  Bignum negative_one(1u, true);
  Bignum one(1u, false);
  auto sum = negative_one + one;
  auto sum2 = one + negative_one;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

TEST(BignumAdditionTest, DigitMaxPlusNegativeDigitMaxIsZero) {
  Bignum zero;
  Bignum negative_digit_max(UINT64_MAX, true);
  Bignum positive_digit_max(UINT64_MAX, false);
  auto sum = negative_digit_max + positive_digit_max;
  auto sum2 = positive_digit_max + negative_digit_max;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

TEST(BignumAdditionTest, MaxTwoDigitPlusNegativeMaxTwoDigitIsZero) {
  Bignum zero;
  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
  Bignum negative_two_digit_max(max_two_digits, true);
  Bignum positive_two_digit_max(std::move(max_two_digits), false);
  auto sum = negative_two_digit_max + positive_two_digit_max;
  auto sum2 = positive_two_digit_max + negative_two_digit_max;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

TEST(BignumAdditionTest, MinTwoDigitPlusNegativeMinTwoDigitIsZero) {
  Bignum zero;
  std::vector<uint64_t> min_two_digit{0u, 1u};
  Bignum negative_two_digit_min(min_two_digit, true);
  Bignum positive_two_digit_min(min_two_digit, false);
  auto sum = negative_two_digit_min + positive_two_digit_min;
  auto sum2 = positive_two_digit_min + negative_two_digit_min;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

TEST(BignumAdditionTest, MaxOneDigitPlusMaxOneDigit) {
  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
  Bignum expected(std::move(expected_digits), false);
  Bignum max_one_digit(UINT64_MAX, false);
  Bignum max_one_digit2(UINT64_MAX, false);
  auto sum = max_one_digit + max_one_digit2;
  auto sum2 = max_one_digit2 + max_one_digit;
  ASSERT_EQ(*sum, expected);
  ASSERT_EQ(*sum2, expected);
}

TEST(BignumAdditionTest, MaxTwoDigitPlusMaxTwoDigit) {
  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
  Bignum expected(std::move(expected_digits), false);
  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
  Bignum max_two_digit(max_two_digits, false);
  Bignum max_two_digit2(std::move(max_two_digits), false);
  auto sum = max_two_digit + max_two_digit2;
  auto sum2 = max_two_digit2 + max_two_digit;
  ASSERT_EQ(*sum, expected);
  ASSERT_EQ(*sum2, expected);
}

TEST(BignumAdditionTest, AdditionCausingCarry) {
  Bignum zero;
  Bignum max_digit(UINT64_MAX, false);
  Bignum one(1u, false);
  std::vector<uint64_t> expected_digits{0u, 1u};
  Bignum expected(expected_digits, false);
  auto sum = max_digit + one;
  auto sum2 = one + max_digit;
  ASSERT_EQ(*sum, expected);
  ASSERT_EQ(*sum2, expected);
}

TEST(BignumAdditionTest, AdditionRequiringBorrow) {
  std::vector<uint64_t> borrowee_digits{0u, 1u};
  Bignum one_zero(borrowee_digits, false);
  Bignum negative_one(1u, true);
  Bignum expected(UINT64_MAX, false);
  auto sum = one_zero + negative_one;
  auto sum2 = negative_one + one_zero;
  ASSERT_EQ(*sum, expected);
  ASSERT_EQ(*sum2, expected);
}

/**
 * Subtraction Tests
 */

TEST(BignumSubtractionTest, ZeroMinusZero) {
  Bignum zero;
  Bignum zero2;
  auto difference = zero - zero2;
  ASSERT_EQ(*difference, zero);
}

TEST(BignumSubtractionTest, NegativeZeroMinusNegativeZero) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum negative_zero2(zero, true);
  auto difference = negative_zero - negative_zero2;
  ASSERT_EQ(*difference, negative_zero);
}
TEST(BignumSubtractionTest, ZeroMinusOne) {
  Bignum zero;
  Bignum one(1u, false);
  Bignum expected(1u, true);
  auto difference = zero - one;
  auto diff2 = Bignum(1u, false) - Bignum(1u, false);
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, ZeroMinusNegativeOne) {
  Bignum zero;
  Bignum negative_one(1u, true);
  Bignum one(1u, false);
  auto difference = zero - negative_one;
  ASSERT_EQ(*difference, one);
}

TEST(BignumAdditionTest, NegativeZeroMinusOne) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum one(1u, false);
  Bignum negative_one(1u, true);
  auto difference = negative_zero - one;
  ASSERT_EQ(*difference, negative_one);
}

TEST(BignumAdditionTest, OneMinusNegativeZero) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum one(1u, false);
  auto difference = one - negative_zero;
  ASSERT_EQ(*difference, one);
}

TEST(BignumAdditionTest, NegativeOneMinusNegativeZero) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum negative_one(1u, true);
  auto difference = negative_one - negative_zero;
  ASSERT_EQ(*difference, negative_one);
}

TEST(BignumAdditionTest, NegativeZeroMinusNegativeOne) {
  Bignum zero;
  Bignum negative_zero(zero, true);
  Bignum negative_one(1u, true);
  Bignum one(1u, false);
  auto difference = negative_zero - negative_one;
  ASSERT_EQ(*difference, one);
}

TEST(BignumSubtractionTest, NegativeOneMinusNegativeOne) {
  Bignum zero;
  Bignum negative_one(1u, true);
  Bignum negative_one2(1u, true);
  auto difference = negative_one - negative_one2;
  ASSERT_EQ(*difference, zero);
}

TEST(BignumSubtractionTest, NegativeDigitMaxMinusNegativeDigitMaxIsZero) {
  Bignum zero;
  Bignum negative_digit_max(UINT64_MAX, true);
  Bignum negative_digit_max2(UINT64_MAX, true);
  auto difference = negative_digit_max - negative_digit_max2;
  ASSERT_EQ(*difference, zero);
}

TEST(BignumSubtractionTest, NegativeMaxTwoDigitMinusNegativeMaxTwoDigitIsZero) {
  Bignum zero;
  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
  Bignum negative_two_digit_max(max_two_digits, true);
  Bignum negative_two_digit_max2(std::move(max_two_digits), true);
  auto difference = negative_two_digit_max - negative_two_digit_max2;
  ASSERT_EQ(*difference, zero);
}

TEST(BignumSubtractionTest, NegativeMinTwoDigitMinusNegativeMinTwoDigitIsZero) {
  Bignum zero;
  std::vector<uint64_t> min_two_digit{0u, 1u};
  Bignum negative_min_two_digit(min_two_digit, true);
  Bignum negative_min_two_digit2(std::move(min_two_digit), true);
  auto difference = negative_min_two_digit - negative_min_two_digit2;
  ASSERT_EQ(*difference, zero);
}

TEST(BignumSubtractionTest, MinTwoDigitMinusNegativeMinTwoDigit) {
  Bignum expected(std::vector<uint64_t>({0u, 2u}), false);
  std::vector<uint64_t> min_two_digits{0u, 1u};
  Bignum min_two_digit(min_two_digits, false);
  Bignum negative_min_two_digit(std::move(min_two_digits), true);
  auto difference = min_two_digit - negative_min_two_digit;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, NegativeMaxOneDigitMinusMaxOneDigit) {
  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
  Bignum expected(std::move(expected_digits), true);
  Bignum negative_max_one_digit(UINT64_MAX, true);
  Bignum max_one_digit(UINT64_MAX, false);
  auto difference = negative_max_one_digit - max_one_digit;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, MaxOneDigitMinusNegativeMaxOneDigit) {
  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, 1u};
  Bignum expected(std::move(expected_digits), false);
  Bignum negative_max_one_digit(UINT64_MAX, true);
  Bignum max_one_digit(UINT64_MAX, false);
  auto difference = max_one_digit - negative_max_one_digit;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, NegativeMaxTwoDigitMinusMaxTwoDigit) {
  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
  Bignum expected(std::move(expected_digits), true);
  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
  Bignum negative_max_two_digit(max_two_digits, true);
  Bignum max_two_digit(std::move(max_two_digits), false);
  auto difference = negative_max_two_digit - max_two_digit;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, PositiveMaxTwoDigitMinusNegativeMaxTwoDigit) {
  std::vector<uint64_t> expected_digits{UINT64_MAX - 1, UINT64_MAX, 1};
  Bignum expected(std::move(expected_digits), false);
  std::vector<uint64_t> max_two_digits{UINT64_MAX, UINT64_MAX};
  Bignum max_two_digit(max_two_digits, false);
  Bignum negative_max_two_digit(std::move(max_two_digits), true);
  auto difference = max_two_digit - negative_max_two_digit;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, SubtractionCausingCarryPositive) {
  Bignum zero;
  Bignum max_digit(UINT64_MAX, false);
  Bignum negative_one(1u, true);
  std::vector<uint64_t> expected_digits{0u, 1u};
  Bignum expected(std::move(expected_digits), false);
  auto difference = max_digit - negative_one;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, SubtractionCausingCarryNegative) {
  Bignum zero;
  Bignum negative_max_digit(UINT64_MAX, true);
  Bignum one(1u, false);
  std::vector<uint64_t> expected_digits{0u, 1u};
  Bignum expected(std::move(expected_digits), true);
  auto difference = negative_max_digit - one;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, SubtractionRequiringBorrowPositive) {
  std::vector<uint64_t> borrowee_digits{0u, 1u};
  Bignum one_zero(std::move(borrowee_digits), false);
  Bignum one(1u, false);
  Bignum expected(UINT64_MAX, false);
  auto difference = one_zero - one;
  ASSERT_EQ(*difference, expected);
}

TEST(BignumSubtractionTest, SubtractionRequiringBorrowNegative) {
  std::vector<uint64_t> borrowee_digits{0u, 1u};
  Bignum one_zero(std::move(borrowee_digits), true);
  Bignum one(1u, true);
  Bignum expected(UINT64_MAX, true);
  auto difference = one_zero - one;
  ASSERT_EQ(*difference, expected);
}

SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    PositiveZeroTimesPositiveZeroIsPositiveZero,
    *, pos_zero, pos_zero,
    pos_zero);


SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    PositiveZeroTimesNegativeZeroIsNegativeZero,
    *, neg_zero, pos_zero,
    neg_zero);

SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    NegativeZeroTimesNegativeZeroIsPositiveZero,
    *, neg_zero, neg_zero,
    pos_zero);

SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    PositiveOneTimesPositiveOneIsPositiveOne,
    *, pos_one, pos_one,
    pos_one);

SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    NegativeOneTimesNegativeOneIsPositiveOne,
    *, neg_one, neg_one,
    pos_one);

SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    PositiveOneTimesNegativeOneIsNegativeOne,
    *, pos_one, neg_one,
    neg_one);

SYMMETRIC_OP_TEST(
    BignumMultiplicationTest,
    PositiveOneTimesZeroIsZero,
    *, pos_one, default_zero,
    default_zero);

TEST(BignumDivisionTests, BignumsUpconvertToRatnumOnDivision) {
  Bignum a(7u, false);
  Bignum b(8u, false);
  Bignum c(3u, false);
  Bignum d(2u, false);
  Ratnum expected("7/8");
  Ratnum expected2("7/3");
  auto result = a / b;
  auto result2 = a / c;
  ASSERT_EQ(*result, expected);
  ASSERT_EQ(*result2, expected2);
}


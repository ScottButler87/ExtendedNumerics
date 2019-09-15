// Copyright 2019 Scott Butler
#include "../src/Bignum.h"
#include <gtest/gtest.h>

TEST(BignumCtorTest, DefaultIsPositiveZero) {
  Bignum zero_default;
  Bignum zero(0u, false);
  ASSERT_EQ(zero_default, zero);
}

TEST(BignumAdditionTest, ZeroPlusZero) {
  Bignum zero;
  Bignum zero2;
  std::unique_ptr<Number> sum = zero + zero2;
  ASSERT_EQ(*sum, zero);
}

TEST(BignumAdditionTest, ZeroPlusOne) {
  Bignum zero;
  Bignum one(1u, false);
  std::unique_ptr<Number> sum = zero + one;
  std::unique_ptr<Number> sum2 = one + zero;
  ASSERT_EQ(*sum, one);
  ASSERT_EQ(*sum2, one);
}

TEST(BignumAdditionTest, ZeroPlusNegativeOne) {
  Bignum zero;
  Bignum negative_one(1u, true);
  std::unique_ptr<Number> sum = zero + negative_one;
  std::unique_ptr<Number> sum2 = negative_one + zero;
  ASSERT_EQ(*sum, negative_one);
  ASSERT_EQ(*sum2, negative_one);
}

TEST(BignumAdditionTest, OnePlusNegativeOne) {
  Bignum zero;
  Bignum negative_one(1u, true);
  Bignum one(1u, false);
  std::unique_ptr<Number> sum = negative_one + one;
  std::unique_ptr<Number> sum2 = one + negative_one;
  ASSERT_EQ(*sum, zero);
  ASSERT_EQ(*sum2, zero);
}

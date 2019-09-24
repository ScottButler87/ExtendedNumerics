// Copyright 2019 Scott Butler

#include "Bignum.h"
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <iostream>

Bignum::Bignum() : digits_(1), isNegative_(false) {}

Bignum::Bignum(const Bignum &o, bool isNegative) noexcept : digits_(o.digits_), isNegative_(isNegative) {}

Bignum::Bignum(Bignum &&other) noexcept : isNegative_(other.isNegative_) {
  digits_ = std::move(other.digits_);
}

Bignum::Bignum(uint64_t value, bool isNegative) : digits_(1), isNegative_(isNegative) {
  digits_[0] = value;
}

Bignum::Bignum(std::vector<uint64_t> &digits, bool isNegative) : digits_(digits), isNegative_(isNegative) {
  TrimLeadingZeros(*this);
}

Bignum::Bignum(std::vector<uint64_t> &&digits, bool isNegative) : digits_(digits), isNegative_(isNegative) {
  TrimLeadingZeros(*this);
}

//Bignum &operator=(std::shared_ptr<const NumericOperations> right) {
//  std::cout << "assignment operator called\n";
//  if (dynamic_cast<const Bignum *>(&right) == this) {
//    return *this;
//  }
//
//  switch (right.numericType()) {
//    case bignum_t: {
//      auto other_bignum = dynamic_cast<const Bignum &>(right);
//      header_ = other_bignum.header_;
//      digits_ = std::vector<uint64_t>(other_bignum.digits_);
//      return *this;
//    }
//    case fixnum_t: {
//      int64_t fixnum = dynamic_cast<const Fixnum &>(right).value();
//      header_.isNegative = (uint64_t) fixnum >> 31u;
//      digits_ = std::vector<uint64_t>(1);
//      digits_.push_back(std::abs(fixnum));
//      return *this;
//    }
//    default: {
//      std::ostringstream what;
//      what << "Conversion from " << right.numericTypeString();
//      what << " to Bignum not allowed";
//      throw std::invalid_argument(what.str());
//    }
//  }
//}

std::unique_ptr<const Bignum> Bignum::operator+(const Bignum &right) const {
  if (right.isZero()) {
    return std::make_unique<Bignum>(*this);
  }
  if (this->isZero()) {
    return std::make_unique<Bignum>(right);
  }
  bool operands_have_same_sign = this->isNegative_ == right.isNegative_;
  if (operands_have_same_sign) {
    return NewBignumWithCombinedMagnitude(*this, right);
  } else {
    bool magnitude_of_this_greater = CompareMagnitude(*this, right) > 0;
    if (magnitude_of_this_greater) {
      return NewBignumWithReducedMagnitude(*this, right);
    } else {
      return NewBignumWithReducedMagnitude(right, *this);
    }
  }
}

std::unique_ptr<const Bignum> Bignum::operator-(const Bignum &right) const {
  if (right.isZero()) {
    return std::make_unique<Bignum>(*this);
  }
  if (this->isZero()) {
    return std::make_unique<Bignum>(right, !right.isNegative_);
  }
  bool operands_have_opposite_sign = this->isNegative_ ^right.isNegative_;
  if (operands_have_opposite_sign) {
    return NewBignumWithCombinedMagnitude(*this, right);
  } else {
    bool magnitude_of_this_greater = CompareMagnitude(*this, right) > 0;
    if (magnitude_of_this_greater) {
      return NewBignumWithReducedMagnitude(*this, right);
    } else {
      return NewBignumWithReducedMagnitude(right, *this);
    }
  }
}

std::unique_ptr<const Bignum> Bignum::operator*(const Bignum &right) const {
  if (this->isZero() || right.isZero()) {
    return std::make_unique<Bignum>();
  }

  if (this->isOne()) {
    return std::make_unique<const Bignum>(*this);
  }

  if (right.isOne()) {
    return std::make_unique<const Bignum>(right);
  }

  bool result_sign = this->isNegative_ ^ right.isNegative_;

  std::vector<uint64_t> product_digits(right.digits_.size() + this->digits_.size() + 1);

  for (auto j_ptr = right.begin(); )



  return std::make_unique<const Bignum>(product_digits, result_sign);
}

bool Bignum::operator==(const Bignum &right) const {
  if (this->isNegative_ != right.isNegative_) {
    return false;
  }
  return this->digits_ == right.digits_;
}

bool inline Bignum::isZero() const {
  return this->digits_.size() == 1 && this->digits_[0] == 0u;
}

bool inline Bignum::isOne() const {
  return this->digits_.size() == 1 && this->digits_[0] == 1u;
}

// Returns a Bignum with the same sign as the sign_dictating_addend, where its magnitude is
// equal to the magnitude of this Bignum plus the magnitude of Bignum right.
std::unique_ptr<Bignum> Bignum::NewBignumWithCombinedMagnitude(const Bignum &sign_dictating_addend,
                                                               const Bignum &addend) const {
  auto sum = std::make_unique<Bignum>(sign_dictating_addend);
  size_t greatest_n = std::max(addend.digits_.size(), sign_dictating_addend.digits_.size());
  sum->digits_.reserve(greatest_n + 1);

  int8_t carry = 0;
  for (size_t i = 0; i < addend.digits_.size(); ++i) {
    sum->digits_[i] = sum->digits_[i] + addend.digits_[i] + carry;
    carry = sum->digits_[i] > addend.digits_[i] ? 0 : sum->digits_[i] == addend.digits_[i] ? carry : 1;
  }
  if (carry != 0) {
    sum->digits_.push_back(carry);
  }
  TrimLeadingZeros(*sum);
  return sum;
}

// Returns a Bignum with the same sign as the reducee, where its magnitude has
// been reduced by the magnitude of the reducer.
std::unique_ptr<Bignum> Bignum::NewBignumWithReducedMagnitude(const Bignum &reducee,
                                                              const Bignum &reducer) const {
  auto difference = std::make_unique<Bignum>(reducee);
  int8_t carry = 0;
  size_t i;
  uint64_t temp;
  for (i = 0; i < reducer.digits_.size(); ++i) {
    temp = difference->digits_[i];
    difference->digits_[i] -= reducer.digits_[i] - carry;
    carry = difference->digits_[i] > temp ? -1 : 0;
  }
  if (carry != 0) {
    difference->digits_[i] += carry;
  }
  TrimLeadingZeros(*difference);
  return difference;
}

int64_t Bignum::CompareMagnitude(const Bignum &left, const Bignum &right) const {
  uint64_t left_size = left.digits_.size();
  uint64_t right_size = right.digits_.size();
  return left_size != right_size ? left_size - right_size : left.digits_[left_size - 1] > right.digits_[right_size - 1];
}

void Bignum::TrimLeadingZeros(Bignum &toTrim) const {
  while (toTrim.digits_.back() == 0 && toTrim.digits_.size() > 1) {
    toTrim.digits_.pop_back();
  }
  // zero is positive
  if (toTrim.digits_.size() == 1 && toTrim.digits_.back() == 0) {
    toTrim.isNegative_ = false;
  }
}

std::ostream &operator<<(std::ostream &os, const Bignum &B) {
  for (unsigned long digit : B.digits_) {
    os << digit << ' ';
  }
  return os;
}

// Copyright 2019 Scott Butler

#include "Boost_Bignum.h"

#include <cstdint>
#include <vector>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/io/ios_state.hpp>

typedef boost::multiprecision::cpp_int cpp_int;

Bignum::Bignum() : internal_rep_() {}

Bignum::Bignum(const Bignum &o, bool is_negative) : internal_rep_(o.internal_rep_) {
  if (is_negative && internal_rep_ >= 0) {
    internal_rep_ *= -1;
  }
}

Bignum::Bignum(Bignum &&other) noexcept : internal_rep_(std::move(other.internal_rep_)) {}

Bignum::Bignum(cpp_int &&op_result) noexcept : internal_rep_(std::move(op_result)) {}

Bignum::Bignum(uint64_t value, bool is_negative) : internal_rep_(value) {
  if (is_negative) {
    internal_rep_ *= -1;
  }
}

Bignum::Bignum(std::vector<uint64_t> &digits, bool is_negative) : internal_rep_() {

  import_bits(internal_rep_, digits.rbegin(), digits.rend());
  if (is_negative) {
    internal_rep_ *= -1;
  }
}

Bignum::Bignum(std::vector<uint64_t> &&digits_to_move, bool is_negative) : internal_rep_() {
  std::vector<uint64_t> digits(digits_to_move);
  import_bits(internal_rep_, digits.rbegin(), digits.rend());
  if (is_negative) {
    internal_rep_ *= -1;
  }
}

std::unique_ptr<const Bignum> Bignum::operator+(const Bignum &right) const {
  cpp_int result = this->internal_rep_ + right.internal_rep_;
  return std::make_unique<Bignum>(std::move(result));
}

std::unique_ptr<const Bignum> Bignum::operator-(const Bignum &right) const {
  cpp_int result = this->internal_rep_ - right.internal_rep_;
  return std::make_unique<Bignum>(std::move(result));
}

std::unique_ptr<const Bignum> Bignum::operator*(const Bignum &right) const {
  cpp_int result = this->internal_rep_ * right.internal_rep_;
  return std::make_unique<Bignum>(std::move(result));
}

std::unique_ptr<const Bignum> Bignum::operator/(const Bignum &right) const {
  cpp_int result = this->internal_rep_ / right.internal_rep_;
  return std::make_unique<Bignum>(std::move(result));
}

bool Bignum::operator==(const Bignum &right) const {
  return this->internal_rep_ == right.internal_rep_;
}

bool inline Bignum::isZero() const {
  return this->internal_rep_ == 0;
}

bool inline Bignum::isOne() const {
  return this->internal_rep_ == 1;
}
bool Bignum::isNegative() const {
  return this->internal_rep_ < 0;
}

std::ostream &operator<<(std::ostream &os, const Bignum &B) {
  boost::io::ios_all_saver guard(os);
  os << std::hex << std::showbase;
  if (B.internal_rep_ < 0) {
    os << '-' << B.internal_rep_ * -1;
  } else {
    os << B.internal_rep_;
  }
  return os;
}

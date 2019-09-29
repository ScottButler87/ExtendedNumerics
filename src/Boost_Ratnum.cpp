// Copyright 2019 Scott Butler

#include "ExtendedNumerics.hpp"

#include <cstdint>
#include <vector>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/io/ios_state.hpp>

typedef boost::multiprecision::cpp_rational cpp_rational;
typedef boost::multiprecision::cpp_int cpp_int;

Ratnum::Ratnum() noexcept : internal_rep_() {}

Ratnum::Ratnum(const Ratnum &o, bool is_negative) noexcept : internal_rep_(o.internal_rep_) {
  if (is_negative && internal_rep_ >= 0) {
    internal_rep_ *= -1;
  }
}

Ratnum::Ratnum(cpp_int &&numerator) noexcept : internal_rep_(numerator) {}

Ratnum::Ratnum(Ratnum &&other) noexcept : internal_rep_(std::move(other.internal_rep_)) {}

Ratnum::Ratnum(cpp_rational &&op_result) noexcept : internal_rep_(op_result) {}

Ratnum::Ratnum(uint64_t value, bool is_negative) noexcept : internal_rep_(value) {
  if (is_negative) {
    internal_rep_ *= -1;
  }
}

Ratnum::Ratnum(uint64_t numerator, uint64_t denominator, bool is_negative) noexcept : internal_rep_(numerator,
                                                                                                    denominator) {
  if (is_negative) {
    internal_rep_ *= -1;
  }
}

Ratnum::Ratnum(const std::string &string_representation) noexcept : internal_rep_(string_representation) {}

Ratnum::Ratnum(cpp_int &&numerator, cpp_int &&denominator) noexcept : internal_rep_(numerator, denominator) {}

std::unique_ptr<const Ratnum> Ratnum::operator+(const Ratnum &right) const {
  cpp_rational result = this->internal_rep_ + right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator+(const Bignum &right) const {
  cpp_rational result = this->internal_rep_ + right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator-(const Ratnum &right) const {
  cpp_rational result = this->internal_rep_ - right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator-(const Bignum &right) const {
  cpp_rational result = this->internal_rep_ - right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator*(const Ratnum &right) const {
  cpp_rational result = this->internal_rep_ * right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator*(const Bignum &right) const {
  cpp_rational result = this->internal_rep_ * right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator/(const Ratnum &right) const {
  cpp_rational result = this->internal_rep_ / right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

std::unique_ptr<const Ratnum> Ratnum::operator/(const Bignum &right) const {
  cpp_rational result = this->internal_rep_ / right.internal_rep_;
  return std::make_unique<Ratnum>(std::move(result));
}

bool Ratnum::operator==(const Ratnum &right) const {
  return this->internal_rep_ == right.internal_rep_;
}

bool Ratnum::operator==(const Bignum &right) const {
  return denominator(this->internal_rep_) == 1 && numerator(this->internal_rep_) == right.internal_rep_;
}

bool inline Ratnum::isZero() const {
  return this->internal_rep_ == 0;
}

bool inline Ratnum::isOne() const {
  return this->internal_rep_ == 1;
}
bool Ratnum::isNegative() const {
  return this->internal_rep_ < 0;
}

std::ostream &operator<<(std::ostream &os, const Ratnum &B) {
  boost::io::ios_all_saver guard(os);
  os << std::hex << std::showbase;
  if (B.internal_rep_ < 0) {
    os << '-' << B.internal_rep_ * -1;
  } else {
    os << B.internal_rep_;
  }
  return os;
}

#include "ExtendedNumerics.hpp"
#include <memory>
#include <iostream>

// TODO optimization: only use cpp_rational when absolutely necessary, it is much slower than cpp_int
// TODO decide how to handle the difference between equality and equivalency in scheme semantics, for example 0.5 is equivalent to 1/2 but they are not equal (0.5 is inexact)

NumericInternal::NumericInternal(const std::string &digits) {
  if (numeric_string_fits_in_signed_fixnum(digits)) {
    fixnum_ = (u64(std::stoll(digits)) << u64(1)) | u64(1);
  } else {
    extended_numeric_ = new BignumInternal(digits);
  }
}

NumericInternal::NumericInternal(const char *digits) {
  if (numeric_string_fits_in_signed_fixnum(digits)) {
    fixnum_ = (u64(std::stoll(digits)) << u64(1) | u64(1));
  } else {
    extended_numeric_ = new BignumInternal(digits);
  }
}

bool Numeric::operator ==(const Numeric &right) const {
  bool this_is_fixnum = this->internal_representation_.isFixnum();
  bool right_is_fixnum = right.internal_representation_.isFixnum();
  if (this_is_fixnum ^ right_is_fixnum) {
    return false;
  }
  if (this_is_fixnum) {
    return this->internal_representation_.asFixnum() == right.internal_representation_.asFixnum();
  } else {
    return *this->internal_representation_.extended_numeric_ == *right.internal_representation_.extended_numeric_;
  }
}

bool Numeric::operator <(const Numeric &right) const {
  bool this_is_fixnum = this->internal_representation_.isFixnum();
  bool right_is_fixnum = right.internal_representation_.isFixnum();
  if (this_is_fixnum ^ right_is_fixnum) {
    return false;
  }
  if (this_is_fixnum) {
    return this->internal_representation_.asFixnum() < right.internal_representation_.asFixnum();
  } else {
    return *this->internal_representation_.extended_numeric_ < *right.internal_representation_.extended_numeric_;
  }
}

std::ostream &operator<<(std::ostream &os, const ExtendedNumerics &num) {
  switch (num.type_) {
    case bignum: os << dynamic_cast<const BignumInternal &>(num);
      break;
    case ratnum: os << dynamic_cast<const RatnumInternal &>(num);
      break;
    case exact_complexnum:os << dynamic_cast<const ExactComplexnumInternal &>(num);
      break;
    case inexact_complexnum:os << dynamic_cast<const InexactComplexnumInternal &>(num);
      break;
    case fixnum: throw std::logic_error("Encountered fixnum while switching on type of ExtendedNumeric for << operator.");
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const BignumInternal &num) {
  os << num.internal_representation_;
  return os;
}

std::ostream &operator<<(std::ostream &os, const RatnumInternal &num) {
  os << num.internal_representation_;
  return os;
}

std::ostream &operator<<(std::ostream &os, const InexactComplexnumInternal &num) {
  os << num.real_ << (num.imaginary_ < 0 ? "" : "+") << num.imaginary_ << 'i';
  return os;
}

std::ostream &operator<<(std::ostream &os, const ExactComplexnumInternal &num) {
  os << num.real_ << (num.imaginary_ < 0 ? "" : "+") << num.imaginary_ << 'i';
  return os;
}

std::ostream &operator<<(std::ostream &os, const Numeric &num) {
  if (num.internal_representation_.isFixnum()) {
    os << num.internal_representation_.asFixnum();
  } else {
    os << *num.internal_representation_.extended_numeric_;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Numeric &&num) {
  return os << num;
}

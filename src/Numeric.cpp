#include "Numeric.hpp"

// TODO optimization: only use cpp_rational when absolutely necessary, it is much slower than cpp_int
// TODO decide how to handle the difference between equality and equivalency in scheme semantics, for example 0.5 is equivalent to 1/2 but they are not equal (0.5 is inexact)

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

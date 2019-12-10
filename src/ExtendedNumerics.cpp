#include <memory>
#include <iostream>
#include "ExtendedNumerics.hpp"
#include "BignumInternal.hpp"
#include "RatnumInternal.hpp"
#include "ExactComplexnumInternal.hpp"
#include "InexactComplexnumInternal.hpp"

std::ostream &operator<<(std::ostream &os, const ExtendedNumerics &num) {
  switch (num.type_) {
    case bignum: os << dynamic_cast<const BignumInternal &>(num);
      break;
    case ratnum: os << dynamic_cast<const RatnumInternal &>(num);
      break;
    case exact_complexnum: os << dynamic_cast<const ExactComplexnumInternal &>(num);
      break;
    case inexact_complexnum: os << dynamic_cast<const InexactComplexnumInternal &>(num);
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

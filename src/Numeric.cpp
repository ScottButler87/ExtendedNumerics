#include "Numeric.hpp"

// TODO optimization: only use cpp_rational when absolutely necessary, it is much slower than cpp_int
// TODO decide how to handle the difference between equality and equivalency in scheme semantics, for example 0.5 is equivalent to 1/2 but they are not equal (0.5 is inexact)
// TODO optimization: use less_than/greater_than to short-circuit a conversion to double for exact comparisons? (bignum, ratnum vs inexact complexnum etc.

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

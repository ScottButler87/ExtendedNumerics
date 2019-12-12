#include "ExtendedNumerics.hpp"
#include "BignumInternal.hpp"
#include "RatnumInternal.hpp"
#include "ExactComplexnumInternal.hpp"
#include "InexactComplexnumInternal.hpp"

/** Bignum addition operators */
const BignumInternal *BignumInternal::operator+(const int64_t &right) const
{
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ + right));
}

const BignumInternal *BignumInternal::operator+(const BignumInternal &right) const
{
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ + right.internal_representation_));
}

const RatnumInternal *BignumInternal::operator+(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ + right.internal_representation_));
}

const ExactComplexnumInternal *BignumInternal::operator+(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(this->internal_representation_ + right.real_, static_cast<cpp_rational>(right.imaginary_));
}

const InexactComplexnumInternal *BignumInternal::operator+(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) + right.real_, right.imaginary_);
}


/** Bignum subtraction operators */
const BignumInternal *BignumInternal::operator-(const int64_t &right) const
{
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ - right));
}

const BignumInternal *BignumInternal::operator-(const BignumInternal &right) const
{
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ - right.internal_representation_));
}

const RatnumInternal *BignumInternal::operator-(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ - right.internal_representation_));
}

const ExactComplexnumInternal *BignumInternal::operator-(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(this->internal_representation_ - right.real_, -right.imaginary_);
}

const InexactComplexnumInternal *BignumInternal::operator-(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) - right.real_, -right.imaginary_);
}


/** Bignum multiplication operators */
const BignumInternal *BignumInternal::operator*(const int64_t &right) const
{
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ * right));
}

const BignumInternal *BignumInternal::operator*(const BignumInternal &right) const
{
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ * right.internal_representation_));
}

const RatnumInternal *BignumInternal::operator*(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ * right.internal_representation_));
}

const ExactComplexnumInternal *BignumInternal::operator*(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(this->internal_representation_ * right.real_, this->internal_representation_ * right.imaginary_);
}

const InexactComplexnumInternal *BignumInternal::operator*(const InexactComplexnumInternal &right) const
{
  double this_as_double = static_cast<double>(this->internal_representation_);
  return new InexactComplexnumInternal(this_as_double * right.real_, this_as_double * right.imaginary_);
}


/** Bignum division operators */
const RatnumInternal *BignumInternal::operator/(const int64_t &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(cpp_rational(this->internal_representation_) / right));
}

const RatnumInternal *BignumInternal::operator/(const BignumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(cpp_rational(this->internal_representation_) / right.internal_representation_));
}

const RatnumInternal *BignumInternal::operator/(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ / right.internal_representation_));
}

const ExactComplexnumInternal *BignumInternal::operator/(const ExactComplexnumInternal &right) const
{
  cpp_rational divisor = right.real_ * right.real_ + right.imaginary_ * right.imaginary_;
  cpp_rational real = this->internal_representation_ * right.real_;
  cpp_rational imaginary = -(this->internal_representation_ * right.imaginary_);
  return new ExactComplexnumInternal(real / divisor, imaginary / divisor);
}

const InexactComplexnumInternal *BignumInternal::operator/(const InexactComplexnumInternal &right) const
{
  double divisor = right.real_ * right.real_ + right.imaginary_ * right.imaginary_;
  double this_as_double = static_cast<double>(this->internal_representation_);
  double real = this_as_double* right.real_;
  double imaginary = -(this_as_double * right.imaginary_);
  return new InexactComplexnumInternal(real / divisor, imaginary / divisor);
}


/** Bignum equality operators */
bool BignumInternal::operator==(const int64_t &right) const
{
  return this->internal_representation_ == right;
}
bool BignumInternal::operator==(const BignumInternal &right) const
{
  return this->internal_representation_ == right.internal_representation_;
}
bool BignumInternal::operator==(const RatnumInternal &right) const
{
  return this->internal_representation_ == right.internal_representation_;
}
bool BignumInternal::operator==(const ExactComplexnumInternal &right) const
{
  return (right.imaginary_ == 0) && (this->internal_representation_ == right.real_);
}
bool BignumInternal::operator==(const InexactComplexnumInternal &right) const
{
  return (right.imaginary_ == 0) && (this->internal_representation_ == static_cast<cpp_rational>(right.real_));
}


/** Bignum inequality operators */
bool BignumInternal::operator!=(const int64_t &right) const
{
  return this->internal_representation_ != right;
}
bool BignumInternal::operator!=(const BignumInternal &right) const
{
  return this->internal_representation_ != right.internal_representation_;
}
bool BignumInternal::operator!=(const RatnumInternal &right) const
{
  return this->internal_representation_ != right.internal_representation_;
}
bool BignumInternal::operator!=(const ExactComplexnumInternal &right) const
{
  return (right.imaginary_ != 0) || (this->internal_representation_ != right.real_);
}
bool BignumInternal::operator!=(const InexactComplexnumInternal &right) const
{
  return (right.imaginary_ != 0) || (this->internal_representation_ != static_cast<cpp_rational>(right.real_));
}


/** Bignum less-than operators */
bool BignumInternal::operator<(const int64_t &right) const
{
  return this->internal_representation_ < right;
}
bool BignumInternal::operator<(const BignumInternal &right) const
{
  return this->internal_representation_ < right.internal_representation_;
}
bool BignumInternal::operator<(const RatnumInternal &right) const
{
  return this->internal_representation_ < right.internal_representation_;
}


/** Bignum/int64_t operators */
const BignumInternal *operator+(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>(left + right.internal_representation_));
}

const BignumInternal *operator-(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>((-right.internal_representation_) + left));
}

const BignumInternal *operator*(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>(right.internal_representation_ * left));
}

const ExtendedNumerics *operator/(int64_t left, const BignumInternal &right) {
  if (left == 0) {
    return new BignumInternal("0");
  }
  cpp_int remainder = left % right.internal_representation_;
  if (remainder != 0) {
    return new RatnumInternal(static_cast<cpp_rational>(cpp_rational(left) / right.internal_representation_));
  } else {
    return new BignumInternal(static_cast<cpp_int>(left / right.internal_representation_));
  }
}

bool operator<(int64_t left, const BignumInternal &right) {
  return left < right.internal_representation_;
}

bool operator==(int64_t left, const BignumInternal &right) {
  return left == right.internal_representation_;
}

bool operator!=(int64_t left, const BignumInternal &right) {
  return left != right.internal_representation_;
}

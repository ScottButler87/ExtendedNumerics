#include "ExtendedNumerics.hpp"
#include "BignumInternal.hpp"
#include "RatnumInternal.hpp"
#include "ExactComplexnumInternal.hpp"
#include "InexactComplexnumInternal.hpp"

/** Deal with issue where cpp_rational cannot handle negative denominators in construction */
RatnumInternal::RatnumInternal(const char *numerator, const char *denominator)
    : ExtendedNumerics(ratnum)
{
  cpp_int num(numerator);
  cpp_int denom(denominator);
  if (denom < 0)
  {
    this->internal_representation_ = cpp_rational(-num, -denom);
  }
  else
  {
    this->internal_representation_ = cpp_rational(num, denom);
  }
}


/** Ratnum addition operators */
const RatnumInternal *RatnumInternal::operator+(const int64_t &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ + right));
}

const RatnumInternal *RatnumInternal::operator+(const BignumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ + right.internal_representation_));
}

const RatnumInternal *RatnumInternal::operator+(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ + right.internal_representation_));
}

const ExactComplexnumInternal *RatnumInternal::operator+(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ + right.real_), static_cast<cpp_rational>(right.imaginary_));
}

const InexactComplexnumInternal *RatnumInternal::operator+(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) + right.real_, right.imaginary_);
}


/** Ratnum subtraction operators */
const RatnumInternal *RatnumInternal::operator-(const int64_t &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ - right));
}

const RatnumInternal *RatnumInternal::operator-(const BignumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ - right.internal_representation_));
}

const RatnumInternal *RatnumInternal::operator-(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ - right.internal_representation_));
}

const ExactComplexnumInternal *RatnumInternal::operator-(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ - right.real_), static_cast<cpp_rational>(-right.imaginary_));
}

const InexactComplexnumInternal *RatnumInternal::operator-(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) - right.real_, -right.imaginary_);
}


/** Ratnum multiplication operators */
const RatnumInternal *RatnumInternal::operator*(const int64_t &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ * right));
}

const RatnumInternal *RatnumInternal::operator*(const BignumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ * right.internal_representation_));
}

const RatnumInternal *RatnumInternal::operator*(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ * right.internal_representation_));
}

const ExactComplexnumInternal *RatnumInternal::operator*(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(this->internal_representation_ * right.real_,
      this->internal_representation_ * right.imaginary_);
}

const InexactComplexnumInternal *RatnumInternal::operator*(const InexactComplexnumInternal &right) const
{
  double this_as_double = static_cast<double>(this->internal_representation_);
  return new InexactComplexnumInternal(this_as_double * right.real_, this_as_double * right.imaginary_);
}


/** Ratnum division operators */
const RatnumInternal *RatnumInternal::operator/(const int64_t &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ / right));
}

const RatnumInternal *RatnumInternal::operator/(const BignumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ / right.internal_representation_));
}

const RatnumInternal *RatnumInternal::operator/(const RatnumInternal &right) const
{
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ / right.internal_representation_));
}

const ExactComplexnumInternal *RatnumInternal::operator/(const ExactComplexnumInternal &right) const
{
  cpp_rational divisor = right.real_ * right.real_ + right.imaginary_ * right.imaginary_;
  cpp_rational real = this->internal_representation_ * right.real_;
  cpp_rational imaginary = -(this->internal_representation_ * right.imaginary_);
  return new ExactComplexnumInternal(real / divisor, imaginary / divisor);
}

const InexactComplexnumInternal *RatnumInternal::operator/(const InexactComplexnumInternal &right) const
{
  double this_as_double = static_cast<double>(this->internal_representation_);
  double divisor = right.real_ * right.real_ + right.imaginary_ * right.imaginary_;
  double real = this_as_double * right.real_;
  double imaginary = -(this_as_double * right.imaginary_);
  return new InexactComplexnumInternal(real / divisor, imaginary / divisor);
}


/** Ratnum equality operators */
bool RatnumInternal::operator==(const int64_t &right) const
{
  return this->internal_representation_ == right;
}

bool RatnumInternal::operator==(const BignumInternal &right) const
{
  return this->internal_representation_ == right.internal_representation_;
}

bool RatnumInternal::operator==(const RatnumInternal &right) const
{
  return this->internal_representation_ == right.internal_representation_;
}

bool RatnumInternal::operator==(const ExactComplexnumInternal &right) const
{
  return (right.imaginary_ == 0) && (this->internal_representation_ == right.real_);
}

bool RatnumInternal::operator==(const InexactComplexnumInternal &right) const
{
  return (right.imaginary_ == 0) && (this->internal_representation_ == right.real_);
}


/** Ratnum inequality operators */
bool RatnumInternal::operator!=(const int64_t &right) const
{
  return this->internal_representation_ != right;
}

bool RatnumInternal::operator!=(const BignumInternal &right) const
{
  return this->internal_representation_ != right.internal_representation_;
}

bool RatnumInternal::operator!=(const RatnumInternal &right) const
{
  return this->internal_representation_ != right.internal_representation_;
}

bool RatnumInternal::operator!=(const ExactComplexnumInternal &right) const
{
  return (right.imaginary_ != 0) || (this->internal_representation_ != right.real_);
}

bool RatnumInternal::operator!=(const InexactComplexnumInternal &right) const {
  return (right.imaginary_ != 0) || (this->internal_representation_ != right.real_);
}


/** Ratnum less-than operators */
bool RatnumInternal::operator<(const int64_t &right) const
{
  return this->internal_representation_ < right;
}

bool RatnumInternal::operator<(const BignumInternal &right) const
{
  return this->internal_representation_ < right.internal_representation_;
}

bool RatnumInternal::operator<(const RatnumInternal &right) const
{
  return this->internal_representation_ < right.internal_representation_;
}


/** Ratnum/int64t operators */
const RatnumInternal *operator+(int64_t left, const RatnumInternal &right)
{
  return new RatnumInternal(static_cast<cpp_rational>(left + right.internal_representation_));
}

const RatnumInternal *operator-(int64_t left, const RatnumInternal &right)
{
  return new RatnumInternal(static_cast<cpp_rational>(left - right.internal_representation_));
}

const RatnumInternal *operator*(int64_t left, const RatnumInternal &right)
{
  return new RatnumInternal(static_cast<cpp_rational>(left * right.internal_representation_));
}

const RatnumInternal *operator/(int64_t left, const RatnumInternal &right)
{
  return new RatnumInternal(static_cast<cpp_rational>(left / right.internal_representation_));
}

bool operator<(int64_t left, const RatnumInternal &right) {
  return left < right.internal_representation_;
}

bool operator==(int64_t left, const RatnumInternal &right) {
  return left == right.internal_representation_;
}

bool operator!=(int64_t left, const RatnumInternal &right) {
  return left != right.internal_representation_;
}


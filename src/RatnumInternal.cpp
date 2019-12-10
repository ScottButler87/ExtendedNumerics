#include "ExtendedNumerics.hpp"

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
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ - right.real_), static_cast<cpp_rational>(right.imaginary_));
}

const InexactComplexnumInternal *RatnumInternal::operator-(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) - right.real_, right.imaginary_);
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
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ * right.real_), static_cast<cpp_rational>(right.imaginary_));
}

const InexactComplexnumInternal *RatnumInternal::operator*(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) * right.real_, right.imaginary_);
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
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ / right.real_), static_cast<cpp_rational>(right.imaginary_));
}

const InexactComplexnumInternal *RatnumInternal::operator/(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) / right.real_, right.imaginary_);
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
  return (right.imaginary_ == 0) && (this->internal_representation_ == static_cast<cpp_rational>(right.real_));
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
  return (right.imaginary_ != 0) || (this->internal_representation_ != static_cast<cpp_rational>(right.real_));
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

#include "ExtendedNumerics.hpp"
#include "BignumInternal.hpp"
#include "RatnumInternal.hpp"
#include "ExactComplexnumInternal.hpp"
#include "InexactComplexnumInternal.hpp"

/** Deal with issue where cpp_rational cannot handle negative denominators in construction */
ExactComplexnumInternal::ExactComplexnumInternal(
    const char *real_numerator,
    const char *real_denominator,
    const char *imaginary_numerator,
    const char *imaginary_denominator)
    : ExtendedNumerics(exact_complexnum)
{
  cpp_int real_num(real_numerator);
  cpp_int real_denom(real_denominator);
  if (real_denom < 0)
  {
    this->real_ = cpp_rational(-real_num, -real_denom);
  }
  else
  {
    this->real_ = cpp_rational(real_num, real_denom);
  }
  cpp_int imaginary_num(imaginary_numerator);
  cpp_int imaginary_denom(imaginary_denominator);
  if (imaginary_denom < 0)
  {
    this->imaginary_ = cpp_rational(-imaginary_num, -imaginary_denom);
  }
  else
  {
    this->imaginary_ = cpp_rational(imaginary_num, imaginary_denom);
  }
}


/** Exact Complexnum addition operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const int64_t &right) const
{
  return new ExactComplexnumInternal(this->real_ + right, cpp_rational(this->imaginary_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const BignumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ + right.internal_representation_, cpp_rational(this->imaginary_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const RatnumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ + right.internal_representation_, cpp_rational(this->imaginary_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ + right.real_, this->imaginary_ + right.imaginary_);
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator+(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->real_) + right.real_,
                                       static_cast<double>(this->imaginary_) + right.imaginary_);
}


/** Exact Complexnum subtraction operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const int64_t &right) const
{
  return new ExactComplexnumInternal(this->real_ - right, cpp_rational(this->imaginary_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const BignumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ - right.internal_representation_, cpp_rational(this->imaginary_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const RatnumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ - right.internal_representation_, cpp_rational(this->imaginary_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ - right.real_, this->imaginary_ - right.imaginary_);
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator-(const InexactComplexnumInternal &right) const
{
  return new InexactComplexnumInternal(static_cast<double>(this->real_) - right.real_,
                                       static_cast<double>(this->imaginary_) - right.imaginary_);
}


/** Exact Complexnum multiplication operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const int64_t &right) const
{
  return new ExactComplexnumInternal(this->real_ * right, this->imaginary_ * right);
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const BignumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ * right.internal_representation_, this->imaginary_ * right.internal_representation_);
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const RatnumInternal &right) const
{
  return new ExactComplexnumInternal(this->real_ * right.internal_representation_, this->imaginary_ * right.internal_representation_);
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const ExactComplexnumInternal &right) const
{
  return new ExactComplexnumInternal((this->real_ * right.real_) - (this->imaginary_ * right.imaginary_),
		                     (this->real_ * right.imaginary_) + (this->imaginary_ * right.real_));
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator*(const InexactComplexnumInternal &right) const
{
  double real_as_double = static_cast<double>(this->real_);
  double imaginary_as_double = static_cast<double>(this->imaginary_);
  return new InexactComplexnumInternal((real_as_double * right.real_) - (imaginary_as_double * right.imaginary_),
		                       (real_as_double * right.imaginary_) + (imaginary_as_double * right.real_));
}


/** Exact Complexnum division operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const int64_t &right) const
{
  cpp_int divisor = cpp_int(right) * right;
  return new ExactComplexnumInternal((this->real_ * right) / divisor, (this->imaginary_ * right) / divisor);
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const BignumInternal &right) const
{
  cpp_int divisor = right.internal_representation_ * right.internal_representation_;
  return new ExactComplexnumInternal((this->real_ * right.internal_representation_) / divisor,
                                     (this->imaginary_ * right.internal_representation_) / divisor);
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const RatnumInternal &right) const
{
  cpp_rational divisor = right.internal_representation_ * right.internal_representation_;
  return new ExactComplexnumInternal((this->real_ * right.internal_representation_) / divisor,
                                     (this->imaginary_ * right.internal_representation_) / divisor);
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const ExactComplexnumInternal &right) const
{
  cpp_rational divisor = (right.real_ * right.real_) + (right.imaginary_ * right.imaginary_);
  cpp_rational real_numerator_ = (this->real_ * right.real_) + (this->imaginary_ * right.imaginary_);
  cpp_rational imaginary_numerator_ = (this->imaginary_ * right.real_) - (this->real_ * right.imaginary_);
  return new ExactComplexnumInternal(real_numerator_ / divisor, imaginary_numerator_ / divisor);
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator/(const InexactComplexnumInternal &right) const
{
  double divisor = (right.real_ * right.real_) + (right.imaginary_ * right.imaginary_);
  double real_numerator_ = (static_cast<double>(this->real_) * right.real_) + (static_cast<double>(this->imaginary_) * right.imaginary_);
  double imaginary_numerator_ = (static_cast<double>(this->imaginary_) * right.real_) - (static_cast<double>(this->real_) * right.imaginary_);
  return new InexactComplexnumInternal(real_numerator_ / divisor, imaginary_numerator_ / divisor);
}


/** Exact Complexnum equality operators */
bool ExactComplexnumInternal::operator==(const int64_t &right) const
{
  return (this->imaginary_ == 0) && (this->real_ == right);
}

bool ExactComplexnumInternal::operator==(const BignumInternal &right) const
{
  return (this->imaginary_ == 0) && (this->real_ == right.internal_representation_);
}

bool ExactComplexnumInternal::operator==(const RatnumInternal &right) const
{
  return (this->imaginary_ == 0) && (this->real_ == right.internal_representation_);
}

bool ExactComplexnumInternal::operator==(const ExactComplexnumInternal &right) const
{
  return (this->imaginary_ == right.imaginary_) && (this->real_ == right.real_);
}

bool ExactComplexnumInternal::operator==(const InexactComplexnumInternal &right) const
{
  return (this->imaginary_ == cpp_rational(right.imaginary_)) && (this->real_ == cpp_rational(right.real_));
}


/** Exact Complexnum inequality operators */
bool ExactComplexnumInternal::operator!=(const int64_t &right) const
{
  return (this->imaginary_ != 0) || (this->real_ != right);
}

bool ExactComplexnumInternal::operator!=(const BignumInternal &right) const
{
  return (this->imaginary_ != 0) || (this->real_ != right.internal_representation_);
}

bool ExactComplexnumInternal::operator!=(const RatnumInternal &right) const
{
  return (this->imaginary_ != 0) || (this->real_ != right.internal_representation_);
}

bool ExactComplexnumInternal::operator!=(const ExactComplexnumInternal &right) const
{
  return (this->imaginary_ != right.imaginary_) || (this->real_ != right.real_);
}

bool ExactComplexnumInternal::operator!=(const InexactComplexnumInternal &right) const
{
  return (this->imaginary_ != cpp_rational(right.imaginary_)) || (this->real_ != cpp_rational(right.real_));
}


/** Exact Complexnum/int64_t operators */
const ExactComplexnumInternal *operator+(int64_t left, const ExactComplexnumInternal &right)
{
  return new ExactComplexnumInternal(left + right.real_, static_cast<cpp_rational>(right.imaginary_));
}

const ExactComplexnumInternal *operator-(int64_t left, const ExactComplexnumInternal &right)
{
  return new ExactComplexnumInternal(left - right.real_, -right.imaginary_);
}

const ExactComplexnumInternal *operator*(int64_t left, const ExactComplexnumInternal &right)
{
  return new ExactComplexnumInternal(left * right.real_, left * right.imaginary_);
}

const ExactComplexnumInternal *operator/(int64_t left, const ExactComplexnumInternal &right)
{
  cpp_rational divisor = (right.real_ * right.real_) + (right.imaginary_ * right.imaginary_);
  cpp_rational real_numerator = left * right.real_;
  cpp_rational imaginary_numerator = -(left * right.imaginary_);
  return new ExactComplexnumInternal(real_numerator / divisor, imaginary_numerator / divisor);
}

bool operator==(int64_t left, const ExactComplexnumInternal &right) {
  return right.imaginary_ == 0 && left == right.real_;
}

bool operator!=(int64_t left, const ExactComplexnumInternal &right) {
  return right.imaginary_ != 0 || left != right.real_;
}

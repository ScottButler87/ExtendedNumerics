#include "ExtendedNumerics.hpp"

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
  cpp_rational &&real_intermediate_ = ((this->real_) + cpp_rational(right));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) + cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const BignumInternal &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) + cpp_rational(right.internal_representation_));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) + cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const RatnumInternal &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) + cpp_rational(right.internal_representation_));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) + cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator+(const ExactComplexnumInternal &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) + cpp_rational(right.real_));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) + cpp_rational(right.imaginary_));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator+(const InexactComplexnumInternal &right) const
{
  double real_intermediate_ = (static_cast<double>(this->real_) + (right.real_));
  double imaginary_intermediate_ = (static_cast<double>(this->imaginary_) + (right.imaginary_));
  return new InexactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}


/** Exact Complexnum subtraction operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const int64_t &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) - cpp_rational(right));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) - cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const BignumInternal &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) - cpp_rational(right.internal_representation_));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) - cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const RatnumInternal &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) - cpp_rational(right.internal_representation_));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) - cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator-(const ExactComplexnumInternal &right) const
{
  cpp_rational &&real_intermediate_ = ((this->real_) - cpp_rational(right.real_));
  cpp_rational &&imaginary_intermediate_ = ((this->imaginary_) - cpp_rational(right.imaginary_));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator-(const InexactComplexnumInternal &right) const
{
  double real_intermediate_ = (static_cast<double>(this->real_) - (right.real_));
  double imaginary_intermediate_ = (static_cast<double>(this->imaginary_) - (right.imaginary_));
  return new InexactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}


/** Exact Complexnum multiplication operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const int64_t &right) const
{
  cpp_rational &&real_product_ = ((this->real_) * cpp_rational(right)) - ((this->imaginary_) * cpp_rational(0));
  cpp_rational &&imaginary_product_ = ((this->real_) * cpp_rational(0)) + ((this->imaginary_) * cpp_rational(right));
  return new ExactComplexnumInternal(std::move(real_product_), std::move(imaginary_product_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const BignumInternal &right) const
{
  cpp_rational &&real_product_ = ((this->real_) * cpp_rational(right.internal_representation_)) - ((this->imaginary_) * cpp_rational(0));
  cpp_rational &&imaginary_product_ = ((this->real_) * cpp_rational(0)) + ((this->imaginary_) * cpp_rational(right.internal_representation_));
  return new ExactComplexnumInternal(std::move(real_product_), std::move(imaginary_product_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const RatnumInternal &right) const
{
  cpp_rational &&real_product_ = ((this->real_) * cpp_rational(right.internal_representation_)) - ((this->imaginary_) * cpp_rational(0));
  cpp_rational &&imaginary_product_ = ((this->real_) * cpp_rational(0)) + ((this->imaginary_) * cpp_rational(right.internal_representation_));
  return new ExactComplexnumInternal(std::move(real_product_), std::move(imaginary_product_));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator*(const ExactComplexnumInternal &right) const
{
  cpp_rational &&real_product_ = ((this->real_) * cpp_rational(right.real_)) - ((this->imaginary_) * cpp_rational(right.imaginary_));
  cpp_rational &&imaginary_product_ = ((this->real_) * cpp_rational(right.imaginary_)) + ((this->imaginary_) * cpp_rational(right.real_));
  return new ExactComplexnumInternal(std::move(real_product_), std::move(imaginary_product_));
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator*(const InexactComplexnumInternal &right) const
{
  double real_product_ = (static_cast<double>(this->real_) * (right.real_)) - (static_cast<double>(this->imaginary_) * (right.imaginary_));
  double imaginary_product_ = (static_cast<double>(this->real_) * (right.imaginary_)) + (static_cast<double>(this->imaginary_) * (right.real_));
  return new InexactComplexnumInternal(std::move(real_product_), std::move(imaginary_product_));
}


/** Exact Complexnum division operators */
const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const int64_t &right) const
{
  cpp_rational &&divisor = cpp_rational((cpp_rational(right) * cpp_rational(right)) + (cpp_rational(0) * cpp_rational(0)));
  cpp_rational &&real_numerator_ = ((this->real_) * cpp_rational(right)) + ((this->imaginary_) * cpp_rational(0));
  cpp_rational &&imaginary_numerator_ = ((this->imaginary_) * cpp_rational(right)) - ((this->real_) * cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_numerator_ / divisor), std::move(imaginary_numerator_ / divisor));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const BignumInternal &right) const
{
  cpp_rational &&divisor = cpp_rational((cpp_rational(right.internal_representation_) * cpp_rational(right.internal_representation_)) + (cpp_rational(0) * cpp_rational(0)));
  cpp_rational &&real_numerator_ = ((this->real_) * cpp_rational(right.internal_representation_)) + ((this->imaginary_) * cpp_rational(0));
  cpp_rational &&imaginary_numerator_ = ((this->imaginary_) * cpp_rational(right.internal_representation_)) - ((this->real_) * cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_numerator_ / divisor), std::move(imaginary_numerator_ / divisor));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const RatnumInternal &right) const
{
  cpp_rational &&divisor = cpp_rational((cpp_rational(right.internal_representation_) * cpp_rational(right.internal_representation_)) + (cpp_rational(0) * cpp_rational(0)));
  cpp_rational &&real_numerator_ = ((this->real_) * cpp_rational(right.internal_representation_)) + ((this->imaginary_) * cpp_rational(0));
  cpp_rational &&imaginary_numerator_ = ((this->imaginary_) * cpp_rational(right.internal_representation_)) - ((this->real_) * cpp_rational(0));
  return new ExactComplexnumInternal(std::move(real_numerator_ / divisor), std::move(imaginary_numerator_ / divisor));
}

const ExactComplexnumInternal *ExactComplexnumInternal::operator/(const ExactComplexnumInternal &right) const
{
  cpp_rational &&divisor = cpp_rational((cpp_rational(right.real_) * cpp_rational(right.real_)) + (cpp_rational(right.imaginary_) * cpp_rational(right.imaginary_)));
  cpp_rational &&real_numerator_ = ((this->real_) * cpp_rational(right.real_)) + ((this->imaginary_) * cpp_rational(right.imaginary_));
  cpp_rational &&imaginary_numerator_ = ((this->imaginary_) * cpp_rational(right.real_)) - ((this->real_) * cpp_rational(right.imaginary_));
  return new ExactComplexnumInternal(std::move(real_numerator_ / divisor), std::move(imaginary_numerator_ / divisor));
}

const InexactComplexnumInternal *ExactComplexnumInternal::operator/(const InexactComplexnumInternal &right) const
{
  double divisor = (((right.real_) * (right.real_)) + ((right.imaginary_) * (right.imaginary_)));
  double real_numerator_ = (static_cast<double>(this->real_) * (right.real_)) + (static_cast<double>(this->imaginary_) * (right.imaginary_));
  double imaginary_numerator_ = (static_cast<double>(this->imaginary_) * (right.real_)) - (static_cast<double>(this->real_) * (right.imaginary_));
  return new InexactComplexnumInternal(std::move(real_numerator_ / divisor), std::move(imaginary_numerator_ / divisor));
}


/** Exact Complexnum/int64_t operators */
const ExactComplexnumInternal *operator+(int64_t left, const ExactComplexnumInternal &right)
{
  cpp_rational real_intermediate_ = (cpp_int(left) + (right.real_));
  cpp_rational imaginary_intermediate_ = (cpp_int(0) + (right.imaginary_));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *operator-(int64_t left, const ExactComplexnumInternal &right)
{
  cpp_rational real_intermediate_ = (cpp_int(left) - (right.real_));
  cpp_rational imaginary_intermediate_ = (cpp_int(0) - (right.imaginary_));
  return new ExactComplexnumInternal(std::move(real_intermediate_), std::move(imaginary_intermediate_));
}

const ExactComplexnumInternal *operator*(int64_t left, const ExactComplexnumInternal &right)
{
  cpp_rational real_product_ = (cpp_int(left) * (right.real_)) - (cpp_int(0) * (right.imaginary_));
  cpp_rational imaginary_product_ = (cpp_int(left) * (right.imaginary_)) + (cpp_int(0) * (right.real_));
  return new ExactComplexnumInternal(std::move(real_product_), std::move(imaginary_product_));
}

const ExactComplexnumInternal *operator/(int64_t left, const ExactComplexnumInternal &right)
{
  cpp_rational divisor = (((right.real_) * (right.real_)) + ((right.imaginary_) * (right.imaginary_)));
  cpp_rational real_numerator_ = (cpp_int(left) * (right.real_)) + (cpp_int(0) * (right.imaginary_));
  cpp_rational imaginary_numerator_ = (cpp_int(0) * (right.real_)) - (cpp_int(left) * (right.imaginary_));
  return new ExactComplexnumInternal(std::move(real_numerator_ / divisor), std::move(imaginary_numerator_ / divisor));
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

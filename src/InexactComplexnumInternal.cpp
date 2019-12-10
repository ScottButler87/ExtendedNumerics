#include "ExtendedNumerics.hpp"
#include "BignumInternal.hpp"
#include "RatnumInternal.hpp"
#include "ExactComplexnumInternal.hpp"
#include "InexactComplexnumInternal.hpp"

/** Inexact Complexnum addition operators */
const InexactComplexnumInternal *InexactComplexnumInternal::operator+(const int64_t &right) const
{
  double real_intermediate_ = ((this->real_) + static_cast<double>(right));
  double imaginary_intermediate_ = ((this->imaginary_) + static_cast<double>(0));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator+(const BignumInternal &right) const
{
  double real_intermediate_ = ((this->real_) + static_cast<double>(right.internal_representation_));
  double imaginary_intermediate_ = ((this->imaginary_) + static_cast<double>(0));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator+(const RatnumInternal &right) const
{
  double real_intermediate_ = ((this->real_) + static_cast<double>(right.internal_representation_));
  double imaginary_intermediate_ = ((this->imaginary_) + static_cast<double>(0));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator+(const ExactComplexnumInternal &right) const
{
  double real_intermediate_ = ((this->real_) + static_cast<double>(right.real_));
  double imaginary_intermediate_ = ((this->imaginary_) + static_cast<double>(right.imaginary_));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator+(const InexactComplexnumInternal &right) const
{
  double real_intermediate_ = ((this->real_) + (right.real_));
  double imaginary_intermediate_ = ((this->imaginary_) + (right.imaginary_));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator-(const int64_t &right) const
{
  double real_intermediate_ = ((this->real_) - static_cast<double>(right));
  double imaginary_intermediate_ = ((this->imaginary_) - static_cast<double>(0));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}


/** Inexact Complexnum subtraction operators */
const InexactComplexnumInternal *InexactComplexnumInternal::operator-(const BignumInternal &right) const
{
  double real_intermediate_ = ((this->real_) - static_cast<double>(right.internal_representation_));
  double imaginary_intermediate_ = ((this->imaginary_) - static_cast<double>(0));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator-(const RatnumInternal &right) const
{
  double real_intermediate_ = ((this->real_) - static_cast<double>(right.internal_representation_));
  double imaginary_intermediate_ = ((this->imaginary_) - static_cast<double>(0));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator-(const ExactComplexnumInternal &right) const
{
  double real_intermediate_ = ((this->real_) - static_cast<double>(right.real_));
  double imaginary_intermediate_ = ((this->imaginary_) - static_cast<double>(right.imaginary_));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator-(const InexactComplexnumInternal &right) const
{
  double real_intermediate_ = ((this->real_) - (right.real_));
  double imaginary_intermediate_ = ((this->imaginary_) - (right.imaginary_));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}


/** Inexact Complexnum multiplication operators */
const InexactComplexnumInternal *InexactComplexnumInternal::operator*(const int64_t &right) const
{
  double real_product_ = ((this->real_) * static_cast<double>(right)) - ((this->imaginary_) * static_cast<double>(0));
  double imaginary_product_ = ((this->real_) * static_cast<double>(0)) + ((this->imaginary_) * static_cast<double>(right));
  return new InexactComplexnumInternal((real_product_), (imaginary_product_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator*(const BignumInternal &right) const
{
  double real_product_ = ((this->real_) * static_cast<double>(right.internal_representation_)) - ((this->imaginary_) * static_cast<double>(0));
  double imaginary_product_ = ((this->real_) * static_cast<double>(0)) + ((this->imaginary_) * static_cast<double>(right.internal_representation_));
  return new InexactComplexnumInternal((real_product_), (imaginary_product_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator*(const RatnumInternal &right) const
{
  double real_product_ = ((this->real_) * static_cast<double>(right.internal_representation_)) - ((this->imaginary_) * static_cast<double>(0));
  double imaginary_product_ = ((this->real_) * static_cast<double>(0)) + ((this->imaginary_) * static_cast<double>(right.internal_representation_));
  return new InexactComplexnumInternal((real_product_), (imaginary_product_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator*(const ExactComplexnumInternal &right) const
{
  double real_product_ = ((this->real_) * static_cast<double>(right.real_)) - ((this->imaginary_) * static_cast<double>(right.imaginary_));
  double imaginary_product_ = ((this->real_) * static_cast<double>(right.imaginary_)) + ((this->imaginary_) * static_cast<double>(right.real_));
  return new InexactComplexnumInternal((real_product_), (imaginary_product_));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator*(const InexactComplexnumInternal &right) const
{
  double real_product_ = ((this->real_) * (right.real_)) - ((this->imaginary_) * (right.imaginary_));
  double imaginary_product_ = ((this->real_) * (right.imaginary_)) + ((this->imaginary_) * (right.real_));
  return new InexactComplexnumInternal((real_product_), (imaginary_product_));
}


/** Inexact Complexnum division operators */
const InexactComplexnumInternal *InexactComplexnumInternal::operator/(const int64_t &right) const
{
  double divisor = static_cast<double>((static_cast<double>(right) * static_cast<double>(right)) + (static_cast<double>(0) * static_cast<double>(0)));
  double real_numerator_ = ((this->real_) * static_cast<double>(right)) + ((this->imaginary_) * static_cast<double>(0));
  double imaginary_numerator_ = ((this->imaginary_) * static_cast<double>(right)) - ((this->real_) * static_cast<double>(0));
  return new InexactComplexnumInternal((real_numerator_ / divisor), (imaginary_numerator_ / divisor));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator/(const BignumInternal &right) const
{
  double divisor = static_cast<double>((static_cast<double>(right.internal_representation_) * static_cast<double>(right.internal_representation_)) + (static_cast<double>(0) * static_cast<double>(0)));
  double real_numerator_ = ((this->real_) * static_cast<double>(right.internal_representation_)) + ((this->imaginary_) * static_cast<double>(0));
  double imaginary_numerator_ = ((this->imaginary_) * static_cast<double>(right.internal_representation_)) - ((this->real_) * static_cast<double>(0));
  return new InexactComplexnumInternal((real_numerator_ / divisor), (imaginary_numerator_ / divisor));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator/(const RatnumInternal &right) const
{
  double divisor = static_cast<double>((static_cast<double>(right.internal_representation_) * static_cast<double>(right.internal_representation_)) + (static_cast<double>(0) * static_cast<double>(0)));
  double real_numerator_ = ((this->real_) * static_cast<double>(right.internal_representation_)) + ((this->imaginary_) * static_cast<double>(0));
  double imaginary_numerator_ = ((this->imaginary_) * static_cast<double>(right.internal_representation_)) - ((this->real_) * static_cast<double>(0));
  return new InexactComplexnumInternal((real_numerator_ / divisor), (imaginary_numerator_ / divisor));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator/(const ExactComplexnumInternal &right) const
{
  double divisor = static_cast<double>((static_cast<double>(right.real_) * static_cast<double>(right.real_)) + (static_cast<double>(right.imaginary_) * static_cast<double>(right.imaginary_)));
  double real_numerator_ = ((this->real_) * static_cast<double>(right.real_)) + ((this->imaginary_) * static_cast<double>(right.imaginary_));
  double imaginary_numerator_ = ((this->imaginary_) * static_cast<double>(right.real_)) - ((this->real_) * static_cast<double>(right.imaginary_));
  return new InexactComplexnumInternal((real_numerator_ / divisor), (imaginary_numerator_ / divisor));
}

const InexactComplexnumInternal *InexactComplexnumInternal::operator/(const InexactComplexnumInternal &right) const
{
  double divisor = (((right.real_) * (right.real_)) + ((right.imaginary_) * (right.imaginary_)));
  double real_numerator_ = ((this->real_) * (right.real_)) + ((this->imaginary_) * (right.imaginary_));
  double imaginary_numerator_ = ((this->imaginary_) * (right.real_)) - ((this->real_) * (right.imaginary_));
  return new InexactComplexnumInternal((real_numerator_ / divisor), (imaginary_numerator_ / divisor));
}


/** Inexact Complexnum/int64_t operators */
const InexactComplexnumInternal *operator+(int64_t left, const InexactComplexnumInternal &right)
{
  double real_intermediate_ = (static_cast<double>(left) + (right.real_));
  double imaginary_intermediate_ = (static_cast<double>(0) + (right.imaginary_));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *operator-(int64_t left, const InexactComplexnumInternal &right)
{
  double real_intermediate_ = (static_cast<double>(left) - (right.real_));
  double imaginary_intermediate_ = (static_cast<double>(0) - (right.imaginary_));
  return new InexactComplexnumInternal((real_intermediate_), (imaginary_intermediate_));
}

const InexactComplexnumInternal *operator*(int64_t left, const InexactComplexnumInternal &right)
{
  double real_product_ = (static_cast<double>(left) * (right.real_)) - (static_cast<double>(0) * (right.imaginary_));
  double imaginary_product_ = (static_cast<double>(left) * (right.imaginary_)) + (static_cast<double>(0) * (right.real_));
  return new InexactComplexnumInternal((real_product_), (imaginary_product_));
}

const InexactComplexnumInternal *operator/(int64_t left, const InexactComplexnumInternal &right)
{
  double divisor = (((right.real_) * (right.real_)) + ((right.imaginary_) * (right.imaginary_)));
  double real_numerator_ = (static_cast<double>(left) * (right.real_)) + (static_cast<double>(0) * (right.imaginary_));
  double imaginary_numerator_ = (static_cast<double>(0) * (right.real_)) - (static_cast<double>(left) * (right.imaginary_));
  return new InexactComplexnumInternal((real_numerator_ / divisor), (imaginary_numerator_ / divisor));
}


/** Inexact Complexnum equality operators */
bool InexactComplexnumInternal::operator==(const int64_t &right) const
{
  return (this->imaginary_ == 0) && (((int64_t)this->real_) == right);
}
bool InexactComplexnumInternal::operator==(const BignumInternal &right) const
{
  return (this->imaginary_ == 0) && (cpp_rational(this->real_) == right.internal_representation_);
}
bool InexactComplexnumInternal::operator==(const RatnumInternal &right) const
{
  return (this->imaginary_ == 0) && (cpp_rational(this->real_) == right.internal_representation_);
}
bool InexactComplexnumInternal::operator==(const ExactComplexnumInternal &right) const
{
  return (cpp_rational(this->imaginary_) == right.imaginary_) && (cpp_rational(this->real_) == right.real_);
}
bool InexactComplexnumInternal::operator==(const InexactComplexnumInternal &right) const
{
  return (this->imaginary_ == right.imaginary_) && (this->real_ == right.real_);
}


/** Inexact Complexnum inequality operators */
bool InexactComplexnumInternal::operator!=(const int64_t &right) const
{
  return (this->imaginary_ != 0) || (((int64_t)this->real_) != right);
}

bool InexactComplexnumInternal::operator!=(const BignumInternal &right) const
{
  return (this->imaginary_ != 0) || (cpp_rational(this->real_) != right.internal_representation_);
}

bool InexactComplexnumInternal::operator!=(const RatnumInternal &right) const
{
  return (this->imaginary_ != 0) || (cpp_rational(this->real_) != right.internal_representation_);
}

bool InexactComplexnumInternal::operator!=(const ExactComplexnumInternal &right) const
{
  return (cpp_rational(this->imaginary_) != right.imaginary_) || (cpp_rational(this->real_) != right.real_);
}

bool InexactComplexnumInternal::operator!=(const InexactComplexnumInternal &right) const
{
  return (this->imaginary_ != right.imaginary_) || (this->real_ != right.real_);
}

bool operator==(int64_t left, const InexactComplexnumInternal &right) {
  return right.imaginary_ == 0 && left == right.real_;
}

bool operator!=(int64_t left, const InexactComplexnumInternal &right) {
  return right.imaginary_ != 0 || left != right.real_;
}

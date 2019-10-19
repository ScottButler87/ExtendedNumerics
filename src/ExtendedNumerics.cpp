//
// Created by scott on 10/13/19.
//

#include "ExtendedNumerics.hpp"
#include <memory>
#include <iostream>
#include <sstream>

#define SWITCH_ON_AND_CAST_TYPE_OF_THIS_FOR_OP(OP)\
  switch(this->type_) {\
    case bignum: return dynamic_cast<const BignumInternal &>(*this) OP right;\
    case ratnum: return dynamic_cast<const RatnumInternal &>(*this) OP right;\
    case exact_complexnum: return dynamic_cast<const ExactComplexnumInternal &>(*this) OP right;\
    case inexact_complexnum: return dynamic_cast<const InexactComplexnumInternal &>(*this) OP right;\
  }

#define DISPATCH_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(OP, RIGHT_TYPE)\
const ExtendedNumerics *ExtendedNumerics::operator OP(const RIGHT_TYPE &right) const {\
  SWITCH_ON_AND_CAST_TYPE_OF_THIS_FOR_OP(OP)\
}

#define DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(OP, RIGHT_TYPE)\
bool ExtendedNumerics::operator OP(const RIGHT_TYPE &right) const {\
  SWITCH_ON_AND_CAST_TYPE_OF_THIS_FOR_OP(OP)\
}

#define DISPATCH_INEQUALITY_COMPARISON_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(OP, RIGHT_TYPE)\
bool ExtendedNumerics::operator OP(const RIGHT_TYPE &right) const {\
  switch(this->type_) {\
    case bignum: return dynamic_cast<const BignumInternal &>(*this) OP right;\
    case ratnum: return dynamic_cast<const RatnumInternal &>(*this) OP right;\
    case exact_complexnum:\
    case inexact_complexnum:\
		 throw std::domain_error(\
		     "complex numbers cannot be totally ordered and inequality comparisons are meaningless");\
  }\
}

#define DISPATCH_ON_TYPE_OF_THIS_FOR(TYPE)\
DISPATCH_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(+, TYPE)\
DISPATCH_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(-, TYPE)\
DISPATCH_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(*, TYPE)\
DISPATCH_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(/, TYPE)\
DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(==, TYPE)\
DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(!=, TYPE)\
DISPATCH_INEQUALITY_COMPARISON_ON_TYPE_OF_THIS_FOR_OP_AND_TYPE(<, TYPE)\

DISPATCH_ON_TYPE_OF_THIS_FOR(int64_t)
DISPATCH_ON_TYPE_OF_THIS_FOR(ExtendedNumerics)

#define SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_OP(OP)\
  switch (right.type_) {\
    case bignum: return *this OP dynamic_cast<const BignumInternal &>(right);\
    case ratnum: return *this OP dynamic_cast<const RatnumInternal &>(right);\
    case exact_complexnum: return *this OP dynamic_cast<const ExactComplexnumInternal &>(right);\
    case inexact_complexnum: return *this OP dynamic_cast<const InexactComplexnumInternal &>(right);\
  }

#define DISPATCH_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, OP)\
const ExtendedNumerics *CLASS::operator OP(const ExtendedNumerics &right) const {\
  SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_OP(OP)\
}

#define DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, OP)\
bool CLASS::operator OP(const ExtendedNumerics &right) const {\
  SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_OP(OP)\
}

#define DISPATCH_INEQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, OP)\
bool CLASS::operator OP(const ExtendedNumerics &right) const {\
switch (right.type_) {\
    case bignum: return *this OP dynamic_cast<const BignumInternal &>(right);\
    case ratnum: return *this OP dynamic_cast<const RatnumInternal &>(right);\
    case exact_complexnum:\
    case inexact_complexnum:\
		 throw std::domain_error(\
		     "complex numbers cannot be totally ordered and inequality comparisons are meaningless");\
  }\
}

#define DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_COMPLEX(CLASS)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, +)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, -)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, *)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, /)\
DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, ==)\
DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, !=)\

#define DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR(CLASS)\
DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_COMPLEX(CLASS)\
DISPATCH_INEQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, <)

DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR(BignumInternal)
DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR(RatnumInternal)
DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_COMPLEX(ExactComplexnumInternal)
DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_COMPLEX(InexactComplexnumInternal)

#define DEFINE_BIGNUM_OPERATOR(OP)\
const BignumInternal *BignumInternal::operator OP(const int64_t &right) const {\
  return new BignumInternal(cpp_int(this->internal_representation_ OP right));\
}\
const BignumInternal *BignumInternal::operator OP(const BignumInternal &right) const {\
  return new BignumInternal(cpp_int(this->internal_representation_ OP right.internal_representation_));\
}\
const RatnumInternal *BignumInternal::operator OP(const RatnumInternal &right) const {\
  return new RatnumInternal(cpp_rational(this->internal_representation_ OP right.internal_representation_));\
}\
const ExactComplexnumInternal *BignumInternal::operator OP(const ExactComplexnumInternal &right) const {\
  return new ExactComplexnumInternal(cpp_rational(this->internal_representation_ OP right.real_),\
    cpp_rational(right.imaginary_));\
}\
const InexactComplexnumInternal *BignumInternal::operator OP(const InexactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) OP right.real_,\
    right.imaginary_);\
}

DEFINE_BIGNUM_OPERATOR(+)
DEFINE_BIGNUM_OPERATOR(-)
DEFINE_BIGNUM_OPERATOR(*)
DEFINE_BIGNUM_OPERATOR(/)

#define DEFINE_INTEGER_COMPARISONS_FOR(CLASS, OP)\
bool CLASS::operator OP(const int64_t &right) const {\
  return this->internal_representation_ OP right;\
}\
bool CLASS::operator OP(const BignumInternal &right) const {\
  return this->internal_representation_ OP right.internal_representation_;\
}\
bool CLASS::operator OP(const RatnumInternal &right) const {\
  return this->internal_representation_ OP right.internal_representation_;\
}

DEFINE_INTEGER_COMPARISONS_FOR(BignumInternal, ==)
DEFINE_INTEGER_COMPARISONS_FOR(BignumInternal, !=)
DEFINE_INTEGER_COMPARISONS_FOR(BignumInternal, <)

#define DEFINE_COMPLEX_EQUALITY_COMPARISONS_FOR(CLASS)\
bool CLASS::operator ==(const ExactComplexnumInternal &right) const {\
  return (right.imaginary_ == 0) && (this->internal_representation_ == right.real_);\
}\
bool CLASS::operator ==(const InexactComplexnumInternal &right) const {\
  return (right.imaginary_ == 0) && (this->internal_representation_ == cpp_rational(right.real_));\
}\
bool CLASS::operator !=(const ExactComplexnumInternal &right) const {\
  return (right.imaginary_ != 0) || (this->internal_representation_ != right.real_);\
}\
bool CLASS::operator !=(const InexactComplexnumInternal &right) const {\
  return (right.imaginary_ != 0) || (this->internal_representation_ != cpp_rational(right.real_));\
}

DEFINE_COMPLEX_EQUALITY_COMPARISONS_FOR(BignumInternal)

#define DEFINE_RATNUM_OPERATOR(OP)\
const RatnumInternal *RatnumInternal::operator OP(const int64_t &right) const {\
  return new RatnumInternal(cpp_rational(this->internal_representation_ OP right));\
}\
const RatnumInternal *RatnumInternal::operator OP(const BignumInternal &right) const {\
  return new RatnumInternal(cpp_rational(this->internal_representation_ OP right.internal_representation_));\
}\
const RatnumInternal *RatnumInternal::operator OP(const RatnumInternal &right) const {\
  return new RatnumInternal(cpp_rational(this->internal_representation_ OP right.internal_representation_));\
}\
const ExactComplexnumInternal *RatnumInternal::operator OP(const ExactComplexnumInternal &right) const {\
  return new ExactComplexnumInternal(cpp_rational(this->internal_representation_ OP right.real_),\
    cpp_rational(right.imaginary_));\
}\
const InexactComplexnumInternal *RatnumInternal::operator OP(const InexactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) OP right.real_,\
    right.imaginary_);\
}

DEFINE_RATNUM_OPERATOR(+)
DEFINE_RATNUM_OPERATOR(-)
DEFINE_RATNUM_OPERATOR(*)
DEFINE_RATNUM_OPERATOR(/)

DEFINE_INTEGER_COMPARISONS_FOR(RatnumInternal, ==)
DEFINE_INTEGER_COMPARISONS_FOR(RatnumInternal, !=)
DEFINE_INTEGER_COMPARISONS_FOR(RatnumInternal, <)
DEFINE_COMPLEX_EQUALITY_COMPARISONS_FOR(RatnumInternal)

#define DEFINE_EXACT_COMPLEXNUM_OPERATOR(OP)\
const ExactComplexnumInternal *ExactComplexnumInternal::operator OP(const int64_t &right) const {\
  return new ExactComplexnumInternal(this->real_ OP right, cpp_rational(this->imaginary_));\
}\
const ExactComplexnumInternal *ExactComplexnumInternal::operator OP(const BignumInternal &right) const {\
  return new ExactComplexnumInternal(this->real_ OP right.internal_representation_, cpp_rational(this->imaginary_));\
}\
const ExactComplexnumInternal *ExactComplexnumInternal::operator OP(const RatnumInternal &right) const {\
  return new ExactComplexnumInternal(this->real_ OP right.internal_representation_, cpp_rational(this->imaginary_));\
}\
const ExactComplexnumInternal *ExactComplexnumInternal::operator OP(const ExactComplexnumInternal &right) const {\
  return new ExactComplexnumInternal(this->real_ OP right.real_, this->imaginary_ OP right.imaginary_);\
}\
const InexactComplexnumInternal *ExactComplexnumInternal::operator OP(const InexactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(static_cast<double>(this->real_) OP right.real_,\
    static_cast<double>(this->imaginary_) OP right.imaginary_);\
}

DEFINE_EXACT_COMPLEXNUM_OPERATOR(+)
DEFINE_EXACT_COMPLEXNUM_OPERATOR(-)
DEFINE_EXACT_COMPLEXNUM_OPERATOR(*)
DEFINE_EXACT_COMPLEXNUM_OPERATOR(/)

bool ExactComplexnumInternal::operator ==(const int64_t &right) const {
  return (this->imaginary_ == 0) && (this->real_ == right);
}
bool ExactComplexnumInternal::operator ==(const BignumInternal &right) const {
  return (this->imaginary_ == 0) && (this->real_ == right.internal_representation_);
}
bool ExactComplexnumInternal::operator ==(const RatnumInternal &right) const {
  return (this->imaginary_ == 0) && (this->real_ == right.internal_representation_);
}
bool ExactComplexnumInternal::operator ==(const ExactComplexnumInternal &right) const {
  return (this->imaginary_ == right.imaginary_) && (this->real_ == right.real_);
}
bool ExactComplexnumInternal::operator ==(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ == cpp_rational(right.imaginary_)) && (this->real_ == cpp_rational(right.real_));
}

bool ExactComplexnumInternal::operator !=(const int64_t &right) const {
  return (this->imaginary_ != 0) || (this->real_ != right);
}
bool ExactComplexnumInternal::operator !=(const BignumInternal &right) const {
  return (this->imaginary_ != 0) || (this->real_ != right.internal_representation_);
}
bool ExactComplexnumInternal::operator !=(const RatnumInternal &right) const {
  return (this->imaginary_ != 0) || (this->real_ != right.internal_representation_);
}
bool ExactComplexnumInternal::operator !=(const ExactComplexnumInternal &right) const {
  return (this->imaginary_ != right.imaginary_) || (this->real_ != right.real_);
}
bool ExactComplexnumInternal::operator !=(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ != cpp_rational(right.imaginary_)) || (this->real_ != cpp_rational(right.real_));
}

#define DEFINE_INEXACT_COMPLEXNUM_OPERATOR(OP)\
const InexactComplexnumInternal *InexactComplexnumInternal::operator OP(const int64_t &right) const {\
  return new InexactComplexnumInternal(this->real_ OP static_cast<double>(right), this->imaginary_);\
}\
const InexactComplexnumInternal *InexactComplexnumInternal::operator OP(const BignumInternal &right) const {\
  return new InexactComplexnumInternal(this->real_ OP static_cast<double>(right.internal_representation_), this->imaginary_);\
}\
const InexactComplexnumInternal *InexactComplexnumInternal::operator OP(const RatnumInternal &right) const {\
  return new InexactComplexnumInternal(this->real_ OP static_cast<double>(right.internal_representation_), this->imaginary_);\
}\
const InexactComplexnumInternal *InexactComplexnumInternal::operator OP(const ExactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(this->real_ OP static_cast<double>(right.real_),\
      this->imaginary_ OP static_cast<double>(right.imaginary_));\
}\
const InexactComplexnumInternal *InexactComplexnumInternal::operator OP(const InexactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(this->real_ OP right.real_,\
    this->imaginary_ OP right.imaginary_);\
}

DEFINE_INEXACT_COMPLEXNUM_OPERATOR(+)
DEFINE_INEXACT_COMPLEXNUM_OPERATOR(-)
DEFINE_INEXACT_COMPLEXNUM_OPERATOR(*)
DEFINE_INEXACT_COMPLEXNUM_OPERATOR(/)

bool InexactComplexnumInternal::operator ==(const int64_t &right) const {
  return (this->imaginary_ == 0) && (((int64_t)this->real_) == right);
}
bool InexactComplexnumInternal::operator ==(const BignumInternal &right) const {
  return (this->imaginary_ == 0) && (cpp_rational(this->real_) == right.internal_representation_);
}
bool InexactComplexnumInternal::operator ==(const RatnumInternal &right) const {
  return (this->imaginary_ == 0) && (cpp_rational(this->real_) == right.internal_representation_);
}
bool InexactComplexnumInternal::operator ==(const ExactComplexnumInternal &right) const {
  return (cpp_rational(this->imaginary_) == right.imaginary_) && (cpp_rational(this->real_) == right.real_);
}
bool InexactComplexnumInternal::operator ==(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ == right.imaginary_) && (this->real_ == right.real_);
}

bool InexactComplexnumInternal::operator !=(const int64_t &right) const {
  return (this->imaginary_ != 0) || (((int64_t)this->real_) != right);
}
bool InexactComplexnumInternal::operator !=(const BignumInternal &right) const {
  return (this->imaginary_ != 0) || (cpp_rational(this->real_) != right.internal_representation_);
}
bool InexactComplexnumInternal::operator !=(const RatnumInternal &right) const {
  return (this->imaginary_ != 0) || (cpp_rational(this->real_) != right.internal_representation_);
}
bool InexactComplexnumInternal::operator !=(const ExactComplexnumInternal &right) const {
  return (cpp_rational(this->imaginary_) != right.imaginary_) || (cpp_rational(this->real_) != right.real_);
}
bool InexactComplexnumInternal::operator !=(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ != right.imaginary_) || (this->real_ != right.real_);
}

Numeric Numeric::operator+(const Numeric &right) const {
  if (this->internal_representation_.isFixnum()) {
    if (right.internal_representation_.isFixnum()) {
      int64_t result = this->internal_representation_.asFixnum() + right.internal_representation_.asFixnum();
      if (result <= MAX_FIXNUM_VALUE && result >= MIN_FIXNUM_VALUE) {
        return Numeric(result);
      } else {
        std::stringstream s;
        s << result;
        return Numeric(s.str());
      }
    } else {
      return Numeric(*right.internal_representation_.extended_numeric_ + this->internal_representation_.asFixnum());
    }
  } else {
    if (right.internal_representation_.isFixnum()) {
      return Numeric(*this->internal_representation_.extended_numeric_ + right.internal_representation_.asFixnum());
    } else {
      return Numeric(
          *this->internal_representation_.extended_numeric_ + *right.internal_representation_.extended_numeric_);
    }
  }
}

NumericInternal::NumericInternal(
    const std::string &digits) {
  if (numeric_string_fits_in_signed_fixnum(digits)) {
    fixnum_ = ((uint64_t) std::stoll(digits) << 1u) | 1u;
  } else {
    extended_numeric_ = new BignumInternal(digits);
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

std::ostream &operator<<(std::ostream &os, Numeric &num) {
  if (num.internal_representation_.isFixnum()) {
    os << num.internal_representation_.asFixnum();
  } else {
    os << *num.internal_representation_.extended_numeric_;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, Numeric &&num) {
  return os << num;
}

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
  }\
  throw std::logic_error("Unknown type encountered switching on this->type_");

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
             "complex numbers have no natural total ordering and inequality comparisons are meaningless");\
  }\
  throw std::logic_error("Unknown type encountered switching on this->type_");\
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

#define SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_LEFT_OPERAND_AND_OP(LEFT_OPERAND, OP)\
switch (right.type_) {\
  case bignum: return LEFT_OPERAND OP dynamic_cast<const BignumInternal &>(right);\
  case ratnum: return LEFT_OPERAND OP dynamic_cast<const RatnumInternal &>(right);\
  case exact_complexnum: return LEFT_OPERAND OP dynamic_cast<const ExactComplexnumInternal &>(right);\
  case inexact_complexnum: return LEFT_OPERAND OP dynamic_cast<const InexactComplexnumInternal &>(right);\
}\
throw std::logic_error("Unknown type encountered switching on right.type_");

#define DISPATCH_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, OP)\
const ExtendedNumerics *CLASS::operator OP(const ExtendedNumerics &right) const {\
  SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_LEFT_OPERAND_AND_OP(*this, OP)\
}

#define DISPATCH_EQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, OP)\
bool CLASS::operator OP(const ExtendedNumerics &right) const {\
  SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_LEFT_OPERAND_AND_OP(*this, OP)\
}

#define DISPATCH_INEQUALITY_COMPARISON_ON_TYPE_OF_RIGHT_FOR_CLASS_AND_OP(CLASS, OP)\
bool CLASS::operator OP(const ExtendedNumerics &right) const {\
switch (right.type_) {\
    case bignum: return *this OP dynamic_cast<const BignumInternal &>(right);\
    case ratnum: return *this OP dynamic_cast<const RatnumInternal &>(right);\
    case exact_complexnum:\
    case inexact_complexnum:\
         throw std::domain_error(\
             "complex numbers have no natural total ordering and inequality comparisons are meaningless");\
  }\
  throw std::logic_error("Unknown type encountered switching on right.type_");\
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

#define DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, OP)\
const ExtendedNumerics *operator OP(TYPE left, const ExtendedNumerics &right) {\
  SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_LEFT_OPERAND_AND_OP(left, OP)\
}

#define DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_BUILTIN_TYPE(TYPE)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, +)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, -)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, *)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, /)

DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_BUILTIN_TYPE(int64_t)

#define DEFINE_BIGNUM_OPERATOR(OP)\
const BignumInternal *BignumInternal::operator OP(const int64_t &right) const {\
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ OP right));\
}\
const BignumInternal *BignumInternal::operator OP(const BignumInternal &right) const {\
  return new BignumInternal(static_cast<cpp_int>(this->internal_representation_ OP right.internal_representation_));\
}\
const RatnumInternal *BignumInternal::operator OP(const RatnumInternal &right) const {\
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ OP right.internal_representation_));\
}\
const ExactComplexnumInternal *BignumInternal::operator OP(const ExactComplexnumInternal &right) const {\
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ OP right.real_),\
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

BignumInternal *operator-(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>(cpp_int(left) - right.internal_representation_));
}

RatnumInternal *operator/(int64_t left, const BignumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(cpp_rational(left) / right.internal_representation_));
}

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

RatnumInternal *operator-(int64_t left, const RatnumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(cpp_rational(left) - right.internal_representation_));
}
RatnumInternal *operator/(int64_t left, const RatnumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(cpp_rational(left) / right.internal_representation_));
}

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
ExactComplexnumInternal *operator-(int64_t left, const ExactComplexnumInternal &right) {
  return new ExactComplexnumInternal(cpp_rational(left) - right.real_, cpp_rational(right.imaginary_));
}


// TODO: fix these, imaginary parts of complex numbers are not closed under multiplication/division
DEFINE_EXACT_COMPLEXNUM_OPERATOR(*)
DEFINE_EXACT_COMPLEXNUM_OPERATOR(/)

bool ExactComplexnumInternal::operator==(const int64_t &right) const {
  return (this->imaginary_ == 0) && (this->real_ == right);
}
bool ExactComplexnumInternal::operator==(const BignumInternal &right) const {
  return (this->imaginary_ == 0) && (this->real_ == right.internal_representation_);
}
bool ExactComplexnumInternal::operator==(const RatnumInternal &right) const {
  return (this->imaginary_ == 0) && (this->real_ == right.internal_representation_);
}
bool ExactComplexnumInternal::operator==(const ExactComplexnumInternal &right) const {
  return (this->imaginary_ == right.imaginary_) && (this->real_ == right.real_);
}
bool ExactComplexnumInternal::operator==(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ == cpp_rational(right.imaginary_)) && (this->real_ == cpp_rational(right.real_));
}

bool ExactComplexnumInternal::operator!=(const int64_t &right) const {
  return (this->imaginary_ != 0) || (this->real_ != right);
}
bool ExactComplexnumInternal::operator!=(const BignumInternal &right) const {
  return (this->imaginary_ != 0) || (this->real_ != right.internal_representation_);
}
bool ExactComplexnumInternal::operator!=(const RatnumInternal &right) const {
  return (this->imaginary_ != 0) || (this->real_ != right.internal_representation_);
}
bool ExactComplexnumInternal::operator!=(const ExactComplexnumInternal &right) const {
  return (this->imaginary_ != right.imaginary_) || (this->real_ != right.real_);
}
bool ExactComplexnumInternal::operator!=(const InexactComplexnumInternal &right) const {
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
InexactComplexnumInternal *operator-(int64_t left, const InexactComplexnumInternal &right) {
  return new InexactComplexnumInternal(static_cast<double>(left) - right.real_, right.imaginary_);
}

// TODO: fix these, imaginary parts of complex numbers are not closed under multiplication/division
DEFINE_INEXACT_COMPLEXNUM_OPERATOR(*)
DEFINE_INEXACT_COMPLEXNUM_OPERATOR(/)

bool InexactComplexnumInternal::operator==(const int64_t &right) const {
  return (this->imaginary_ == 0) && (((int64_t) this->real_) == right);
}
bool InexactComplexnumInternal::operator==(const BignumInternal &right) const {
  return (this->imaginary_ == 0) && (cpp_rational(this->real_) == right.internal_representation_);
}
bool InexactComplexnumInternal::operator==(const RatnumInternal &right) const {
  return (this->imaginary_ == 0) && (cpp_rational(this->real_) == right.internal_representation_);
}
bool InexactComplexnumInternal::operator==(const ExactComplexnumInternal &right) const {
  return (cpp_rational(this->imaginary_) == right.imaginary_) && (cpp_rational(this->real_) == right.real_);
}
bool InexactComplexnumInternal::operator==(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ == right.imaginary_) && (this->real_ == right.real_);
}

bool InexactComplexnumInternal::operator!=(const int64_t &right) const {
  return (this->imaginary_ != 0) || (((int64_t) this->real_) != right);
}
bool InexactComplexnumInternal::operator!=(const BignumInternal &right) const {
  return (this->imaginary_ != 0) || (cpp_rational(this->real_) != right.internal_representation_);
}
bool InexactComplexnumInternal::operator!=(const RatnumInternal &right) const {
  return (this->imaginary_ != 0) || (cpp_rational(this->real_) != right.internal_representation_);
}
bool InexactComplexnumInternal::operator!=(const ExactComplexnumInternal &right) const {
  return (cpp_rational(this->imaginary_) != right.imaginary_) || (cpp_rational(this->real_) != right.real_);
}
bool InexactComplexnumInternal::operator!=(const InexactComplexnumInternal &right) const {
  return (this->imaginary_ != right.imaginary_) || (this->real_ != right.real_);
}

NumericInternal::NumericInternal(const std::string &digits) {
  if (numeric_string_fits_in_signed_fixnum(digits)) {
    fixnum_ = ((uint64_t) std::stoll(digits) << 1u) | 1u;
  } else {
    extended_numeric_ = new BignumInternal(digits);
  }
}

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

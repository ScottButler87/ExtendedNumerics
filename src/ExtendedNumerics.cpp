//
// Created by scott on 10/13/19.
//

#include "ExtendedNumerics.hpp"
#include <memory>
#include <iostream>

// TODO optimization: only use cpp_rational when absolutely necessary, it is much slower than cpp_int

#define SWITCH_ON_AND_CAST_TYPE_OF_THIS_FOR_OP(OP)\
  if (PRINT_DEBUG) std::cout << "Switching on type of this: " << this->type_ << std::endl;\
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
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ OP right));\
}\
const RatnumInternal *RatnumInternal::operator OP(const BignumInternal &right) const {\
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ OP right.internal_representation_));\
}\
const RatnumInternal *RatnumInternal::operator OP(const RatnumInternal &right) const {\
  return new RatnumInternal(static_cast<cpp_rational>(this->internal_representation_ OP right.internal_representation_));\
}\
const ExactComplexnumInternal *RatnumInternal::operator OP(const ExactComplexnumInternal &right) const {\
  return new ExactComplexnumInternal(static_cast<cpp_rational>(this->internal_representation_ OP right.real_),\
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

#define GENERIC_COMPLEX_ADDITION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, PRIMITIVE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator +(const RIGHT_TYPE &right) const {\
  PRIMITIVE_RESULT_TYPE real_intermediate_ = (THIS_CAST(ACCESS_THIS_REAL) + RIGHT_CAST(ACCESS_RIGHT_REAL));\
  PRIMITIVE_RESULT_TYPE imaginary_intermediate_ = (THIS_CAST(ACCESS_THIS_IMAGINARY) + RIGHT_CAST(ACCESS_RIGHT_IMAGINARY));\
  return new RETURN_TYPE(MOVE_OPERATION(real_intermediate_), MOVE_OPERATION(imaginary_intermediate_));\
}

#define GENERIC_COMPLEX_SUBTRACTION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, PRIMITIVE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator -(const RIGHT_TYPE &right) const {\
  PRIMITIVE_RESULT_TYPE real_intermediate_ = (THIS_CAST(ACCESS_THIS_REAL) - RIGHT_CAST(ACCESS_RIGHT_REAL));\
  PRIMITIVE_RESULT_TYPE imaginary_intermediate_ = (THIS_CAST(ACCESS_THIS_IMAGINARY) - RIGHT_CAST(ACCESS_RIGHT_IMAGINARY));\
  return new RETURN_TYPE(MOVE_OPERATION(real_intermediate_), MOVE_OPERATION(imaginary_intermediate_));\
}


#define GENERIC_COMPLEX_MULTIPLICATION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, PRIMITIVE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator *(const RIGHT_TYPE &right) const {\
  PRIMITIVE_RESULT_TYPE real_product_ = (THIS_CAST(ACCESS_THIS_REAL) * RIGHT_CAST(ACCESS_RIGHT_REAL)) - (THIS_CAST(ACCESS_THIS_IMAGINARY) * RIGHT_CAST(ACCESS_RIGHT_IMAGINARY));\
  PRIMITIVE_RESULT_TYPE imaginary_product_ = (THIS_CAST(ACCESS_THIS_REAL) * RIGHT_CAST(ACCESS_RIGHT_IMAGINARY)) + (THIS_CAST(ACCESS_THIS_IMAGINARY) * RIGHT_CAST(ACCESS_RIGHT_REAL));\
  return new RETURN_TYPE(MOVE_OPERATION(real_product_), MOVE_OPERATION(imaginary_product_));\
}

#define GENERIC_COMPLEX_DIVISION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, PRIMITIVE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator /(const RIGHT_TYPE &right) const {\
  PRIMITIVE_RESULT_TYPE divisor = RIGHT_CAST((ACCESS_RIGHT_REAL * ACCESS_RIGHT_REAL) + (ACCESS_RIGHT_IMAGINARY * ACCESS_RIGHT_IMAGINARY));\
  PRIMITIVE_RESULT_TYPE real_numerator_ = (THIS_CAST(ACCESS_THIS_REAL) * RIGHT_CAST(ACCESS_RIGHT_REAL)) + (THIS_CAST(ACCESS_THIS_IMAGINARY) * RIGHT_CAST(ACCESS_RIGHT_IMAGINARY));\
  PRIMITIVE_RESULT_TYPE imaginary_numerator_ = (THIS_CAST(ACCESS_THIS_IMAGINARY) * RIGHT_CAST(ACCESS_RIGHT_REAL)) - (THIS_CAST(ACCESS_THIS_REAL) * RIGHT_CAST(ACCESS_RIGHT_IMAGINARY)) ;\
  return new RETURN_TYPE(MOVE_OPERATION(real_numerator_/divisor), MOVE_OPERATION(imaginary_numerator_/divisor));\
}

#define DEFINE_COMPLEX_OPERATION(OPERATION, RETURN_TYPE_FOR_EXACT\
                                    , DEFINITION_CLASS, PRIMITIVE_RESULT_TYPE\
                                    , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY\
                                    , THIS_CAST, RIGHT_CAST\
                                    , INEXACT_THIS_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, int64_t, PRIMITIVE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right, 0,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, BignumInternal, PRIMITIVE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.internal_representation_, 0,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, RatnumInternal, PRIMITIVE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.internal_representation_, 0,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, ExactComplexnumInternal, PRIMITIVE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.real_, right.imaginary_,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(InexactComplexnumInternal, DEFINITION_CLASS, InexactComplexnumInternal, double,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.real_, right.imaginary_,\
      INEXACT_THIS_CAST,, MOVE_OPERATION)

#define DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_OP) DEFINE_COMPLEX_OPERATION(GENERIC_COMPLEX_OP,\
      ExactComplexnumInternal, ExactComplexnumInternal, cpp_rational&&,\
      this->real_, this->imaginary_, , cpp_rational, static_cast<double>, std::move)

DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_ADDITION)
DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_SUBTRACTION)
DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_MULTIPLICATION)
DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_DIVISION)

ExactComplexnumInternal *operator-(int64_t left, const ExactComplexnumInternal &right) {
  return new ExactComplexnumInternal(cpp_rational(left) - right.real_, cpp_rational(right.imaginary_));
}


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

#define DEFINE_INEXACT_COMPLEX_OPERATION(OPERATION) \
DEFINE_COMPLEX_OPERATION(OPERATION, InexactComplexnumInternal, InexactComplexnumInternal, double,\
                         this->real_, this->imaginary_, , static_cast<double>, ,)

DEFINE_INEXACT_COMPLEX_OPERATION(GENERIC_COMPLEX_ADDITION)
DEFINE_INEXACT_COMPLEX_OPERATION(GENERIC_COMPLEX_SUBTRACTION)
DEFINE_INEXACT_COMPLEX_OPERATION(GENERIC_COMPLEX_MULTIPLICATION)
DEFINE_INEXACT_COMPLEX_OPERATION(GENERIC_COMPLEX_DIVISION)

InexactComplexnumInternal *operator-(int64_t left, const InexactComplexnumInternal &right) {
  return new InexactComplexnumInternal(static_cast<double>(left) - right.real_, right.imaginary_);
}

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

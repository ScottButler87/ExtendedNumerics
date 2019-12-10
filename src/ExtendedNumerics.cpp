//
// Created by scott on 10/13/19.
//

#include "ExtendedNumerics.hpp"
#include <memory>
#include <iostream>

// TODO optimization: only use cpp_rational when absolutely necessary, it is much slower than cpp_int
// TODO decide how to handle the difference between equality and equivalency in scheme semantics, for example 0.5 is equivalent to 1/2 but they are not equal (0.5 is inexact)

#define SWITCH_ON_AND_CAST_TYPE_OF_THIS_FOR_OP(OP)\
  if (PRINT_DEBUG) std::cout << "Switching on type of this: " << this->type_ << std::endl;\
  switch(this->type_) {\
    case bignum: return dynamic_cast<const BignumInternal &>(*this) OP right;\
    case ratnum: return dynamic_cast<const RatnumInternal &>(*this) OP right;\
    case exact_complexnum: return dynamic_cast<const ExactComplexnumInternal &>(*this) OP right;\
    case inexact_complexnum: return dynamic_cast<const InexactComplexnumInternal &>(*this) OP right;\
    case fixnum: throw std::logic_error("Encountered fixnum while switching on type of this");\
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
    case fixnum: throw std::logic_error("Encountered fixnum while switching on type of right");\
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
  case fixnum: throw std::logic_error("Encountered fixnum while switching on type of right for builtin");\
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
    case fixnum: throw std::logic_error("Encountered fixnum while switching on type of right for inequality comparison");\
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

#define DISPATCH_COMPARISON_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, OP)\
bool operator OP(TYPE left, const ExtendedNumerics &right) {\
  SWITCH_ON_AND_CAST_TYPE_OF_RIGHT_FOR_LEFT_OPERAND_AND_OP(left, OP)\
}

#define DISPATCH_ON_TYPE_OF_RIGHT_OPERAND_FOR_BUILTIN_TYPE(TYPE)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, +)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, -)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, *)\
DISPATCH_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, /)\
DISPATCH_COMPARISON_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, <)\
DISPATCH_COMPARISON_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, !=)\
DISPATCH_COMPARISON_ON_TYPE_OF_RIGHT_FOR_BUILTIN_TYPE_AND_OP(TYPE, ==)

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
    static_cast<cpp_rational>(right.imaginary_));\
}\
const InexactComplexnumInternal *BignumInternal::operator OP(const InexactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) OP right.real_,\
    right.imaginary_);\
}

DEFINE_BIGNUM_OPERATOR(+)
DEFINE_BIGNUM_OPERATOR(-)
DEFINE_BIGNUM_OPERATOR(*)
DEFINE_BIGNUM_OPERATOR(/)

const BignumInternal *operator+(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>(left + right.internal_representation_));
}

const BignumInternal *operator-(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>(left - right.internal_representation_));
}

const BignumInternal *operator*(int64_t left, const BignumInternal &right) {
  return new BignumInternal(static_cast<cpp_int>(left * right.internal_representation_));
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
  return (right.imaginary_ == 0) && (this->internal_representation_ == static_cast<cpp_rational>(right.real_));\
}\
bool CLASS::operator !=(const ExactComplexnumInternal &right) const {\
  return (right.imaginary_ != 0) || (this->internal_representation_ != right.real_);\
}\
bool CLASS::operator !=(const InexactComplexnumInternal &right) const {\
  return (right.imaginary_ != 0) || (this->internal_representation_ != static_cast<cpp_rational>(right.real_));\
}

DEFINE_COMPLEX_EQUALITY_COMPARISONS_FOR(BignumInternal)


RatnumInternal::RatnumInternal(const char* numerator, const char* denominator)
  : ExtendedNumerics(ratnum) {
    // deal with negative denominators, cpp_rational throws seemingly unnecessary exceptions for negative denominators
    cpp_int num(numerator);
    cpp_int denom(denominator);
    if ( denom < 0) {
      this->internal_representation_ = cpp_rational(-num, -denom);
    } else {
      this->internal_representation_ = cpp_rational(num, denom);
    }
}

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
    static_cast<cpp_rational>(right.imaginary_));\
}\
const InexactComplexnumInternal *RatnumInternal::operator OP(const InexactComplexnumInternal &right) const {\
  return new InexactComplexnumInternal(static_cast<double>(this->internal_representation_) OP right.real_,\
    right.imaginary_);\
}

DEFINE_RATNUM_OPERATOR(+)
DEFINE_RATNUM_OPERATOR(-)
DEFINE_RATNUM_OPERATOR(*)
DEFINE_RATNUM_OPERATOR(/)


const RatnumInternal *operator+(int64_t left, const RatnumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(left + right.internal_representation_));
}

const RatnumInternal *operator-(int64_t left, const RatnumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(left - right.internal_representation_));
}
const RatnumInternal *operator*(int64_t left, const RatnumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(left * right.internal_representation_));
}

const RatnumInternal *operator/(int64_t left, const RatnumInternal &right) {
  return new RatnumInternal(static_cast<cpp_rational>(left / right.internal_representation_));
}

DEFINE_INTEGER_COMPARISONS_FOR(RatnumInternal, ==)
DEFINE_INTEGER_COMPARISONS_FOR(RatnumInternal, !=)
DEFINE_INTEGER_COMPARISONS_FOR(RatnumInternal, <)

DEFINE_COMPLEX_EQUALITY_COMPARISONS_FOR(RatnumInternal)

#define COMPLEX_ADDITION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_LEFT_REAL, ACCESS_LEFT_IMAGINARY,\
      ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, LEFT_CAST_TO_INTERMEDIATE, RIGHT_CAST_TO_INTERMEDIATE, MOVE_OPERATION)\
  INTERMEDIATE_RESULT_TYPE real_intermediate_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_REAL) + RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL));\
  INTERMEDIATE_RESULT_TYPE imaginary_intermediate_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_IMAGINARY) + RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY));\
  return new RETURN_TYPE(MOVE_OPERATION(real_intermediate_), MOVE_OPERATION(imaginary_intermediate_));

#define GENERIC_COMPLEX_ADDITION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, INTERMEDIATE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator +(const RIGHT_TYPE &right) const {\
  COMPLEX_ADDITION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
        ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
}

#define COMPLEX_SUBTRACTION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_LEFT_REAL, ACCESS_LEFT_IMAGINARY,\
		ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, LEFT_CAST_TO_INTERMEDIATE, RIGHT_CAST_TO_INTERMEDIATE, MOVE_OPERATION)\
  INTERMEDIATE_RESULT_TYPE real_intermediate_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_REAL) - RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL));\
  INTERMEDIATE_RESULT_TYPE imaginary_intermediate_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_IMAGINARY) - RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY));\
  return new RETURN_TYPE(MOVE_OPERATION(real_intermediate_), MOVE_OPERATION(imaginary_intermediate_));\


#define GENERIC_COMPLEX_SUBTRACTION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, INTERMEDIATE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator -(const RIGHT_TYPE &right) const {\
  COMPLEX_SUBTRACTION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
        ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
}

#define COMPLEX_MULTIPLICATION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_LEFT_REAL, ACCESS_LEFT_IMAGINARY,\
      ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, LEFT_CAST_TO_INTERMEDIATE, RIGHT_CAST_TO_INTERMEDIATE, MOVE_OPERATION)\
  INTERMEDIATE_RESULT_TYPE real_product_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_REAL) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL)) - (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_IMAGINARY) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY));\
  INTERMEDIATE_RESULT_TYPE imaginary_product_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_REAL) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY)) + (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_IMAGINARY) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL));\
  return new RETURN_TYPE(MOVE_OPERATION(real_product_), MOVE_OPERATION(imaginary_product_));\


#define GENERIC_COMPLEX_MULTIPLICATION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, INTERMEDIATE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator *(const RIGHT_TYPE &right) const {\
  COMPLEX_MULTIPLICATION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
}


#define GENERIC_COMPLEX_DIVISION(RETURN_TYPE, DEFINITION_CLASS, RIGHT_TYPE, INTERMEDIATE_RESULT_TYPE\
                             , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY, ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY\
                             , THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
const RETURN_TYPE *DEFINITION_CLASS::operator /(const RIGHT_TYPE &right) const {\
  COMPLEX_DIVISION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
}

#define COMPLEX_DIVISION_BODY(RETURN_TYPE, INTERMEDIATE_RESULT_TYPE, ACCESS_LEFT_REAL, ACCESS_LEFT_IMAGINARY,\
      ACCESS_RIGHT_REAL, ACCESS_RIGHT_IMAGINARY, LEFT_CAST_TO_INTERMEDIATE, RIGHT_CAST_TO_INTERMEDIATE, MOVE_OPERATION)\
  INTERMEDIATE_RESULT_TYPE divisor = RIGHT_CAST_TO_INTERMEDIATE((RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL))\
      + (RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY)));\
  INTERMEDIATE_RESULT_TYPE real_numerator_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_REAL) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL))\
      + (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_IMAGINARY) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY));\
  INTERMEDIATE_RESULT_TYPE imaginary_numerator_ = (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_IMAGINARY) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_REAL))\
      - (LEFT_CAST_TO_INTERMEDIATE(ACCESS_LEFT_REAL) * RIGHT_CAST_TO_INTERMEDIATE(ACCESS_RIGHT_IMAGINARY)) ;\
  return new RETURN_TYPE(MOVE_OPERATION(real_numerator_/divisor), MOVE_OPERATION(imaginary_numerator_/divisor));
  

#define DEFINE_COMPLEX_OPERATION(OPERATION, RETURN_TYPE_FOR_EXACT\
                                    , DEFINITION_CLASS, INTERMEDIATE_RESULT_TYPE\
                                    , ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY\
                                    , THIS_CAST, RIGHT_CAST\
                                    , INEXACT_THIS_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, int64_t, INTERMEDIATE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right, 0,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, BignumInternal, INTERMEDIATE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.internal_representation_, 0,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, RatnumInternal, INTERMEDIATE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.internal_representation_, 0,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(RETURN_TYPE_FOR_EXACT, DEFINITION_CLASS, ExactComplexnumInternal, INTERMEDIATE_RESULT_TYPE,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.real_, right.imaginary_,\
      THIS_CAST, RIGHT_CAST, MOVE_OPERATION)\
  OPERATION(InexactComplexnumInternal, DEFINITION_CLASS, InexactComplexnumInternal, double,\
      ACCESS_THIS_REAL, ACCESS_THIS_IMAGINARY,\
      right.real_, right.imaginary_,\
      INEXACT_THIS_CAST,, MOVE_OPERATION)

ExactComplexnumInternal::ExactComplexnumInternal(
    const char *real_numerator,
    const char *real_denominator,
    const char *imaginary_numerator,
    const char *imaginary_denominator)
      : ExtendedNumerics(exact_complexnum) {
  // deal with negative denominators, cpp_rational throws seemingly unnecessary exceptions for negative denominators
  cpp_int real_num(real_numerator);
  cpp_int real_denom(real_denominator);
  if ( real_denom < 0) {
    this->real_ = cpp_rational(-real_num, -real_denom);
  } else {
    this->real_ = cpp_rational(real_num, real_denom);
  }
  cpp_int imaginary_num(imaginary_numerator);
  cpp_int imaginary_denom(imaginary_denominator);
  if ( imaginary_denom < 0) {
    this->imaginary_ = cpp_rational(-imaginary_num, -imaginary_denom);
  } else {
    this->imaginary_ = cpp_rational(imaginary_num, imaginary_denom);
  }
}

#define DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_OP) DEFINE_COMPLEX_OPERATION(GENERIC_COMPLEX_OP,\
      ExactComplexnumInternal, ExactComplexnumInternal, cpp_rational&&,\
      this->real_, this->imaginary_, , cpp_rational, static_cast<double>, std::move)

DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_ADDITION)
DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_SUBTRACTION)
DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_MULTIPLICATION)
DEFINE_EXACT_COMPLEXNUM_OPERATION(GENERIC_COMPLEX_DIVISION)

const ExactComplexnumInternal *operator+(int64_t left, const ExactComplexnumInternal &right) {
  COMPLEX_ADDITION_BODY(ExactComplexnumInternal, cpp_rational, left, 0,\
      right.real_, right.imaginary_, cpp_int,,std::move)\
}

const ExactComplexnumInternal *operator-(int64_t left, const ExactComplexnumInternal &right) {
  COMPLEX_SUBTRACTION_BODY(ExactComplexnumInternal, cpp_rational, left, 0,\
      right.real_, right.imaginary_, cpp_int,,std::move)\
}

const ExactComplexnumInternal *operator*(int64_t left, const ExactComplexnumInternal &right) {
  COMPLEX_MULTIPLICATION_BODY(ExactComplexnumInternal, cpp_rational, left, 0,\
      right.real_, right.imaginary_, cpp_int,,std::move)\
}

const ExactComplexnumInternal *operator/(int64_t left, const ExactComplexnumInternal &right) {
  COMPLEX_DIVISION_BODY(ExactComplexnumInternal, cpp_rational, left, 0,\
      right.real_, right.imaginary_, cpp_int,,std::move)\
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

const InexactComplexnumInternal *operator+(int64_t left, const InexactComplexnumInternal &right) {
  COMPLEX_ADDITION_BODY(InexactComplexnumInternal, double, left, 0,\
        right.real_, right.imaginary_, static_cast<double>,,)
}

const InexactComplexnumInternal *operator-(int64_t left, const InexactComplexnumInternal &right) {
  COMPLEX_SUBTRACTION_BODY(InexactComplexnumInternal, double, left, 0,\
        right.real_, right.imaginary_, static_cast<double>,,)
}

const InexactComplexnumInternal *operator*(int64_t left, const InexactComplexnumInternal &right) {
  COMPLEX_MULTIPLICATION_BODY(InexactComplexnumInternal, double, left, 0,\
        right.real_, right.imaginary_, static_cast<double>,,)
}

const InexactComplexnumInternal *operator/(int64_t left, const InexactComplexnumInternal &right) {
  COMPLEX_DIVISION_BODY(InexactComplexnumInternal, double, left, 0,\
      right.real_, right.imaginary_, static_cast<double>,,)
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
    fixnum_ = (u64(std::stoll(digits)) << u64(1)) | u64(1);
  } else {
    extended_numeric_ = new BignumInternal(digits);
  }
}

NumericInternal::NumericInternal(const char *digits) {
  if (numeric_string_fits_in_signed_fixnum(digits)) {
    fixnum_ = (u64(std::stoll(digits)) << u64(1) | u64(1));
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

bool Numeric::operator <(const Numeric &right) const {
  bool this_is_fixnum = this->internal_representation_.isFixnum();
  bool right_is_fixnum = right.internal_representation_.isFixnum();
  if (this_is_fixnum ^ right_is_fixnum) {
    return false;
  }
  if (this_is_fixnum) {
    return this->internal_representation_.asFixnum() < right.internal_representation_.asFixnum();
  } else {
    return *this->internal_representation_.extended_numeric_ < *right.internal_representation_.extended_numeric_;
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
    case fixnum: throw std::logic_error("Encountered fixnum while switching on type of ExtendedNumeric for << operator.");
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

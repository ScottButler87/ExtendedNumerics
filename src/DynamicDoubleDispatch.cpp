#include "ExtendedNumerics.hpp"

/** MACROS LEFT UNEXPANDED INTENTIONALLY
 *
 *  Does not affect debugging since any route into this file is immediately routed out again.
 *  The macros are easier to understand than the 800+ lines of code they expand to.
 *
 *  Any additional built-ins will need to have dispatching added here before implementing the backing
 *  functions for the mathematical operations.
 */

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

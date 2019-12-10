#ifndef WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_
#define WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_

#include "boost/multiprecision/cpp_int.hpp"
#include "util.hpp"
#include <cstdlib>

//TODO extend functionality: add more Numeric/cprimitive operation overloads

#define ENABLE_GMP 0
#define PRINT_DEBUG 1

#define PTR_RETURN_NUM_OP_DECL(OP_SYMBOL, RETURN_TYPE, ARG_TYPE)\
virtual const RETURN_TYPE *operator OP_SYMBOL(const ARG_TYPE &right) const

#define FRIEND_PTR_RETURN_OP_DECL(OP_SYMBOL, RETURN_TYPE, LEFT_TYPE, RIGHT_TYPE) \
friend const RETURN_TYPE *operator OP_SYMBOL(LEFT_TYPE left, const RIGHT_TYPE &right);

#define NUM_COMP_DECL(OP_SYMBOL, ARG_TYPE)\
virtual bool operator OP_SYMBOL(const ARG_TYPE &right) const;

#define FRIEND_NUM_COMP_DECL(OP_SYMBOL, LEFT_TYPE, RIGHT_TYPE) \
friend bool operator OP_SYMBOL(LEFT_TYPE left, const RIGHT_TYPE &right);

#ifndef SWIGGING_EXTENSION
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE
#endif

#define STR_IMPLEMENTATION \
FORCE_INLINE std::string str() const override {\
  return internal_representation_.str();\
};

#define INEQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(OP_SYMBOL)\
NUM_COMP_DECL(OP_SYMBOL, int64_t)\
NUM_COMP_DECL(OP_SYMBOL, ExtendedNumerics)\
NUM_COMP_DECL(OP_SYMBOL, BignumInternal)\
NUM_COMP_DECL(OP_SYMBOL, RatnumInternal)

#define EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(OP_SYMBOL)\
INEQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(OP_SYMBOL)\
NUM_COMP_DECL(OP_SYMBOL, ExactComplexnumInternal)\
NUM_COMP_DECL(OP_SYMBOL, InexactComplexnumInternal)

// switch to GMP backend for cpp_ints
#if ENABLE_GMP == 1
#include "boost/multiprecision/gmp.hpp"
typedef boost::multiprecision::mpq_rational cpp_rational;
typedef boost::multiprecision::mpz_int cpp_int;
#else
typedef boost::multiprecision::cpp_rational cpp_rational;
typedef boost::multiprecision::cpp_int cpp_int;
#endif
enum ExtendedNumericType {
  bignum = 0,
  ratnum = 1,
  exact_complexnum = 2,
  inexact_complexnum = 3,
  fixnum = 4
};

class BignumInternal;
class RatnumInternal;
class ExactComplexnumInternal;
class InexactComplexnumInternal;
class Numeric;

class ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const ExtendedNumerics &num);

#define DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_BUILTIN_TYPE(BUILTIN_TYPE)\
  FRIEND_PTR_RETURN_OP_DECL(+, ExtendedNumerics, BUILTIN_TYPE, ExtendedNumerics)\
  FRIEND_PTR_RETURN_OP_DECL(-, ExtendedNumerics, BUILTIN_TYPE, ExtendedNumerics)\
  FRIEND_PTR_RETURN_OP_DECL(*, ExtendedNumerics, BUILTIN_TYPE, ExtendedNumerics)\
  FRIEND_PTR_RETURN_OP_DECL(/, ExtendedNumerics, BUILTIN_TYPE, ExtendedNumerics)\
  FRIEND_NUM_COMP_DECL(<, BUILTIN_TYPE, ExtendedNumerics)\
  FRIEND_NUM_COMP_DECL(==, BUILTIN_TYPE, ExtendedNumerics)\
  FRIEND_NUM_COMP_DECL(!=, BUILTIN_TYPE, ExtendedNumerics)

  DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_BUILTIN_TYPE(int64_t)
 public:
  ExtendedNumericType type_;
  ExtendedNumerics(const ExtendedNumerics &to_copy) = delete;
  ExtendedNumerics(ExtendedNumerics &&to_move) = delete;
  virtual ~ExtendedNumerics() = default;
  virtual std::string str() const = 0;

#define DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_TYPE(TYPE)\
  PTR_RETURN_NUM_OP_DECL(+, ExtendedNumerics, TYPE);\
  PTR_RETURN_NUM_OP_DECL(-, ExtendedNumerics, TYPE);\
  PTR_RETURN_NUM_OP_DECL(*, ExtendedNumerics, TYPE);\
  PTR_RETURN_NUM_OP_DECL(/, ExtendedNumerics, TYPE);\
  NUM_COMP_DECL(<, TYPE)\
  NUM_COMP_DECL(==, TYPE)\
  NUM_COMP_DECL(!=, TYPE)

  DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_TYPE(int64_t)
  DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_TYPE(ExtendedNumerics)

 protected:
  explicit ExtendedNumerics(ExtendedNumericType type) : type_(type) {}
};

class BignumInternal : public ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const BignumInternal &num);
  friend const BignumInternal *operator+(int64_t, const BignumInternal &);
  friend const BignumInternal *operator-(int64_t, const BignumInternal &);
  friend const BignumInternal *operator*(int64_t, const BignumInternal &);
  friend const ExtendedNumerics *operator/(int64_t, const BignumInternal &);
  friend class RatnumInternal;
  friend class ExactComplexnumInternal;
  friend class InexactComplexnumInternal;
  friend union NumericInternal;
//  virtual ExtendedNumerics *int64_t_div(int64_t left) const override;
//  virtual const ExtendedNumerics *dispatch_div(int64_t left) const override;
 public:
  explicit BignumInternal(const char *digits) : ExtendedNumerics(bignum), internal_representation_(digits) {}
  explicit BignumInternal(const std::string &digits)
      : BignumInternal(digits.c_str()) {}
  explicit BignumInternal(const cpp_int &int_rep)
      : ExtendedNumerics(bignum), internal_representation_(int_rep) {}
  explicit BignumInternal(cpp_int &&int_rep) noexcept
      : ExtendedNumerics(bignum), internal_representation_(std::move(int_rep)) {}
  BignumInternal(const BignumInternal &to_copy) : BignumInternal(cpp_int(to_copy.internal_representation_)) {}
  BignumInternal(BignumInternal &&to_move) : BignumInternal(std::move(to_move.internal_representation_)) {}

  STR_IMPLEMENTATION

#define DECLARE_BIGNUM_OPERATOR(OP)\
  PTR_RETURN_NUM_OP_DECL(OP, ExtendedNumerics, ExtendedNumerics);\
  PTR_RETURN_NUM_OP_DECL(OP, BignumInternal, int64_t);\
  PTR_RETURN_NUM_OP_DECL(OP, BignumInternal, BignumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, RatnumInternal, RatnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, ExactComplexnumInternal, ExactComplexnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, InexactComplexnumInternal);

  DECLARE_BIGNUM_OPERATOR(+)
  DECLARE_BIGNUM_OPERATOR(-)
  DECLARE_BIGNUM_OPERATOR(*)
  DECLARE_BIGNUM_OPERATOR(/)

  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(==)
  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(!=)
  INEQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(<)
 private:
  cpp_int internal_representation_;
};

class RatnumInternal : public ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &, const RatnumInternal &);
  friend const RatnumInternal *operator+(int64_t, const RatnumInternal &);
  friend const RatnumInternal *operator-(int64_t, const RatnumInternal &);
  friend const RatnumInternal *operator*(int64_t, const RatnumInternal &);
  friend const RatnumInternal *operator/(int64_t, const RatnumInternal &);
  friend class BignumInternal;
  friend class ExactComplexnumInternal;
  friend class InexactComplexnumInternal;
  friend union NumericInternal;
//  virtual ExtendedNumerics *int64_t_div(int64_t left) const override;
//  virtual const ExtendedNumerics *dispatch_div(int64_t left) const override;
 public:
  RatnumInternal(const char *numerator, const char *denominator);
  RatnumInternal(const std::string &numerator, const std::string &denominator)
      : RatnumInternal(numerator.c_str(), denominator.c_str()) {}
  explicit RatnumInternal(cpp_rational &&int_rep)
      : ExtendedNumerics(ratnum), internal_representation_(std::move(int_rep)) {}
  RatnumInternal(const RatnumInternal &to_copy) : RatnumInternal(cpp_rational(to_copy.internal_representation_)) {}
  RatnumInternal(RatnumInternal &&to_move) : RatnumInternal(std::move(to_move.internal_representation_)) {}

  STR_IMPLEMENTATION

#define DECLARE_RATNUM_OPERATOR(OP)\
  PTR_RETURN_NUM_OP_DECL(OP, ExtendedNumerics, ExtendedNumerics);\
  PTR_RETURN_NUM_OP_DECL(OP, RatnumInternal, int64_t);\
  PTR_RETURN_NUM_OP_DECL(OP, RatnumInternal, BignumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, RatnumInternal, RatnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, ExactComplexnumInternal, ExactComplexnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, InexactComplexnumInternal);

  DECLARE_RATNUM_OPERATOR(+)
  DECLARE_RATNUM_OPERATOR(-)
  DECLARE_RATNUM_OPERATOR(*)
  DECLARE_RATNUM_OPERATOR(/)

  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(==)
  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(!=)
  INEQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(<)
 private:
  cpp_rational internal_representation_;
};

class ExactComplexnumInternal : public ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const ExactComplexnumInternal &num);
  friend const ExactComplexnumInternal *operator+(int64_t, const ExactComplexnumInternal &);
  friend const ExactComplexnumInternal *operator-(int64_t, const ExactComplexnumInternal &);
  friend const ExactComplexnumInternal *operator*(int64_t, const ExactComplexnumInternal &);
  friend const ExactComplexnumInternal *operator/(int64_t, const ExactComplexnumInternal &);
  friend class BignumInternal;
  friend class RatnumInternal;
  friend class InexactComplexnumInternal;
  friend union NumericInternal;
 public:
  ExactComplexnumInternal(const char *real_numerator,
                          const char *real_denominator,
                          const char *imaginary_numerator,
                          const char *imaginary_denominator);
  ExactComplexnumInternal(const std::string &real_numerator,
                          const std::string &real_denominator,
                          const std::string &imaginary_numerator,
                          const std::string &imaginary_denominator)
      : ExactComplexnumInternal(real_numerator.c_str(), real_denominator.c_str(),
                                imaginary_numerator.c_str(), imaginary_denominator.c_str()) {}
  ExactComplexnumInternal(cpp_rational &&real, cpp_rational &&imaginary)
      : ExtendedNumerics(exact_complexnum),
        real_(std::move(real)),
        imaginary_(std::move(imaginary)) {}
  ExactComplexnumInternal(const ExactComplexnumInternal &to_copy)
      : ExactComplexnumInternal(cpp_rational(to_copy.real_), cpp_rational(to_copy.imaginary_)) {}
  ExactComplexnumInternal(ExactComplexnumInternal &&to_move)
      : ExactComplexnumInternal(std::move(to_move.real_), std::move(to_move.imaginary_)) {}

  FORCE_INLINE std::string str() const override {
    if (real_ < 0) {
      return (real_.str() + imaginary_.str());
    } else {
      return (real_.str() + "+" + imaginary_.str());
    }
  }

#define DECLARE_EXACT_COMPLEXNUM_OPERATOR(OP)\
  PTR_RETURN_NUM_OP_DECL(OP, ExtendedNumerics, ExtendedNumerics);\
  PTR_RETURN_NUM_OP_DECL(OP, ExactComplexnumInternal, int64_t);\
  PTR_RETURN_NUM_OP_DECL(OP, ExactComplexnumInternal, BignumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, ExactComplexnumInternal, RatnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, ExactComplexnumInternal, ExactComplexnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, InexactComplexnumInternal);

  DECLARE_EXACT_COMPLEXNUM_OPERATOR(+)
  DECLARE_EXACT_COMPLEXNUM_OPERATOR(-)
  DECLARE_EXACT_COMPLEXNUM_OPERATOR(*)
  DECLARE_EXACT_COMPLEXNUM_OPERATOR(/)

  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(==)
  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(!=)
 private:
  cpp_rational real_;
  cpp_rational imaginary_;
};

class InexactComplexnumInternal : public ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const InexactComplexnumInternal &num);
  friend const InexactComplexnumInternal *operator+(int64_t, const InexactComplexnumInternal &);
  friend const InexactComplexnumInternal *operator-(int64_t, const InexactComplexnumInternal &);
  friend const InexactComplexnumInternal *operator*(int64_t, const InexactComplexnumInternal &);
  friend const InexactComplexnumInternal *operator/(int64_t, const InexactComplexnumInternal &);
  friend class BignumInternal;
  friend class RatnumInternal;
  friend class ExactComplexnumInternal;
  friend union NumericInternal;
//  virtual ExtendedNumerics *int64_t_div(int64_t left) const override;
//  virtual const ExtendedNumerics *dispatch_div(int64_t left) const override;
 public:
  InexactComplexnumInternal(double real, double imaginary)
      : ExtendedNumerics(inexact_complexnum), real_(real), imaginary_(imaginary) {}
  InexactComplexnumInternal(const InexactComplexnumInternal &to_copy)
      : InexactComplexnumInternal(to_copy.real_, to_copy.imaginary_) {}
  InexactComplexnumInternal(InexactComplexnumInternal &&to_move)
      : InexactComplexnumInternal(to_move.real_, to_move.imaginary_) {}

  FORCE_INLINE std::string str() const override {
    std::stringstream out;
    if (imaginary_ < 0) {
      out << std::setprecision(64) << real_ << " " << imaginary_ << "i";
    } else {
      out << std::setprecision(64) << real_ << " +" << imaginary_ << "i";
    }
    return out.str();
  }

#define DECLARE_INEXACT_COMPLEXNUM_OPERATOR(OP)\
  PTR_RETURN_NUM_OP_DECL(OP, ExtendedNumerics, ExtendedNumerics);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, int64_t);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, BignumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, RatnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, ExactComplexnumInternal);\
  PTR_RETURN_NUM_OP_DECL(OP, InexactComplexnumInternal, InexactComplexnumInternal);

  DECLARE_INEXACT_COMPLEXNUM_OPERATOR(+)
  DECLARE_INEXACT_COMPLEXNUM_OPERATOR(-)
  DECLARE_INEXACT_COMPLEXNUM_OPERATOR(*)
  DECLARE_INEXACT_COMPLEXNUM_OPERATOR(/)

  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(==)
  EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(!=)
 private:
  double real_;
  double imaginary_;
};

union NumericInternal {
  friend Numeric;
  int64_t fixnum_;
  const ExtendedNumerics *extended_numeric_;
  FORCE_INLINE bool isFixnum() const { return u64(fixnum_) & u64(1); }
  FORCE_INLINE int64_t asFixnum() const {
    if (fixnum_ < 0) {
      return i64((u64(fixnum_) >> u64(1)) | (u64(1) << u64(63)));
    } else {
      return i64(u64(fixnum_) >> u64(1));
    }
  }
  FORCE_INLINE std::string str() {
    if (this->isFixnum()) {
      return std::to_string(this->asFixnum());
    }
    return extended_numeric_->str();
  }
  ~NumericInternal() { if (!isFixnum()) { delete extended_numeric_; }}

  explicit NumericInternal(int64_t num) noexcept
      : fixnum_((u64(num) << u64(1)) | u64(1)) {}
  explicit NumericInternal(const ExtendedNumerics *num) : extended_numeric_(num) {}
  explicit NumericInternal(const std::string &digits);
  explicit NumericInternal(const char *digits);
  NumericInternal(double real, double imaginary)
      : extended_numeric_(new InexactComplexnumInternal(real, imaginary)) {}
  NumericInternal(const std::string &numerator, const std::string &denominator)
      : extended_numeric_(new RatnumInternal(numerator, denominator)) {}
  NumericInternal(const char *numerator, const char *denominator)
      : extended_numeric_(new RatnumInternal(numerator, denominator)) {}
  NumericInternal(const std::string &real_numerator,
                  const std::string &real_denominator,
                  const std::string &imaginary_numerator,
                  const std::string &imaginary_denominator)
      : extended_numeric_(new ExactComplexnumInternal(real_numerator,
                                                      real_denominator,
                                                      imaginary_numerator,
                                                      imaginary_denominator)) {};
  NumericInternal(const char *real_numerator,
                  const char *real_denominator,
                  const char *imaginary_numerator,
                  const char *imaginary_denominator)
      : extended_numeric_(new ExactComplexnumInternal(real_numerator,
                                                      real_denominator,
                                                      imaginary_numerator,
                                                      imaginary_denominator)) {};
  NumericInternal(cpp_rational &&real, cpp_rational &&imaginary) : extended_numeric_(
      new ExactComplexnumInternal(std::move(real), std::move(imaginary))
  ) {}
  NumericInternal(cpp_int &&internal) : extended_numeric_(
      new BignumInternal(std::move(internal))) {}
  NumericInternal(cpp_rational &&internal) : extended_numeric_(
      new RatnumInternal(std::move(internal))) {}
  NumericInternal(const NumericInternal &to_copy) {
    if (to_copy.isFixnum()) {
      this->fixnum_ = to_copy.fixnum_;
    } else {
      switch (to_copy.extended_numeric_->type_) {
        case bignum:
          this->extended_numeric_ =
              new BignumInternal(*dynamic_cast<const BignumInternal *>(to_copy.extended_numeric_));
          break;
        case ratnum:
          this->extended_numeric_ =
              new RatnumInternal(*dynamic_cast<const RatnumInternal *>(to_copy.extended_numeric_));
          break;
        case exact_complexnum:
          this->extended_numeric_ =
              new ExactComplexnumInternal(*dynamic_cast<const ExactComplexnumInternal *>(to_copy.extended_numeric_));
          break;
        case inexact_complexnum:
          this->extended_numeric_ =
              new InexactComplexnumInternal(*dynamic_cast<const InexactComplexnumInternal *>(to_copy.extended_numeric_));
          break;
        case fixnum:
          throw std::logic_error("In NumericInternal copy constructor, isFixnum returned false but extended_numeric_.type_ was fixnum");
      }
    }
  }
  NumericInternal(NumericInternal &&to_move) {
    if (to_move.isFixnum()) {
      this->fixnum_ = to_move.fixnum_;
    } else {
      this->extended_numeric_ = to_move.extended_numeric_;
      to_move.fixnum_ |= 1u;
    }

  }
};

#define INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_INTO_INT_64_T(OPERATOR) \
FORCE_INLINE Numeric operator OPERATOR(const Numeric &right) const {\
  bool this_is_fixnum = this->internal_representation_.isFixnum();\
  bool right_is_fixnum = right.internal_representation_.isFixnum();\
  if (this_is_fixnum && right_is_fixnum) {\
    int64_t result = this->internal_representation_.asFixnum() OPERATOR right.internal_representation_.asFixnum();\
    if (result <= MAX_FIXNUM_VALUE && result >= MIN_FIXNUM_VALUE) {\
      return Numeric(result);\
    } else {\
      std::stringstream s;\
      s << result;\
      return Numeric(s.str());\
    }\
  }\
  if (right_is_fixnum) {\
    return Numeric(*this->internal_representation_.extended_numeric_ OPERATOR right.internal_representation_.asFixnum());\
  }\
  if (this_is_fixnum) {\
    return Numeric(this->internal_representation_.asFixnum() OPERATOR *right.internal_representation_.extended_numeric_);\
  }\
  return Numeric(\
      *this->internal_representation_.extended_numeric_ OPERATOR *right.internal_representation_.extended_numeric_);\
}

#define INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_IN_FIXNUM(OP)\
FORCE_INLINE Numeric operator OP(const Numeric &right) const {\
  bool this_is_fixnum = this->internal_representation_.isFixnum();\
  bool right_is_fixnum = right.internal_representation_.isFixnum();\
  if (this_is_fixnum && right_is_fixnum) {\
    int64_t this_as_fixnum = this->internal_representation_.asFixnum();\
    int64_t right_as_fixnum = right.internal_representation_.asFixnum();\
    int64_t quotient = this_as_fixnum / right_as_fixnum;\
    int64_t remainder = this_as_fixnum % right_as_fixnum;\
    if (remainder == 0)\
      return Numeric(quotient);\
    else if (right_as_fixnum < 0) {\
      return Numeric(cpp_rational(-this_as_fixnum, -right_as_fixnum));\
    } else {\
      return Numeric(cpp_rational(this_as_fixnum, right_as_fixnum));\
    }\
  }\
  if (right_is_fixnum) {\
    return Numeric(*this->internal_representation_.extended_numeric_ OP right.internal_representation_.asFixnum());\
  }\
  if (this_is_fixnum) {\
    return Numeric(this->internal_representation_.asFixnum() OP *right.internal_representation_.extended_numeric_);\
  }\
  return Numeric(\
          *this->internal_representation_.extended_numeric_ OP *right.internal_representation_.extended_numeric_);\
}

#define INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_INTO_INT_128_T(OPERATOR) \
FORCE_INLINE Numeric operator OPERATOR(const Numeric &right) const {\
  bool this_is_fixnum = this->internal_representation_.isFixnum();\
  bool right_is_fixnum = right.internal_representation_.isFixnum();\
  if (this_is_fixnum && right_is_fixnum) {\
    int64_t this_as_fixnum = this->internal_representation_.asFixnum();\
    int64_t right_as_fixnum = right.internal_representation_.asFixnum();\
    boost::multiprecision::int128_t result = boost::multiprecision::int128_t(this_as_fixnum) * right_as_fixnum;\
    if (result <= MAX_FIXNUM_VALUE && result >= MIN_FIXNUM_VALUE) {\
      return Numeric(static_cast<int64_t>(result));\
    } else {\
      std::stringstream s;\
      s << result;\
      return Numeric(s.str());\
    }\
  }\
  if (right_is_fixnum) {\
    return Numeric(*this->internal_representation_.extended_numeric_ OPERATOR right.internal_representation_.asFixnum());\
  }\
  if (this_is_fixnum) {\
    return Numeric(this->internal_representation_.asFixnum() OPERATOR *right.internal_representation_.extended_numeric_);\
  }\
  return Numeric(\
      *this->internal_representation_.extended_numeric_ OPERATOR *right.internal_representation_.extended_numeric_);\
}

class Numeric {
 public:
  explicit Numeric(int64_t num) noexcept : internal_representation_(num) {}
  explicit Numeric(const ExtendedNumerics *num) : internal_representation_(num) {}
  explicit Numeric(const std::string &digits) : internal_representation_(digits) {}
  explicit Numeric(const char *digits) : internal_representation_(digits) {}
  Numeric(double real, double imaginary) : internal_representation_(real, imaginary) {}
  Numeric(cpp_int &&internal) : internal_representation_(std::move(internal)) {}
  Numeric(cpp_rational &&internal) : internal_representation_(std::move(internal)) {}
  Numeric(cpp_rational &&real, cpp_rational &&imaginary) : internal_representation_(
      std::move(real), std::move(imaginary)) {}
  Numeric(const std::string &numerator, const std::string &denominator)
      : internal_representation_(numerator, denominator) {}
  Numeric(const char *numerator, const char *denominator)
      : internal_representation_(numerator, denominator) {}
  Numeric(const std::string &real_numerator, const std::string &real_denominator,
          const std::string &imaginary_numerator, const std::string &imaginary_denominator)
      : internal_representation_(real_numerator,
                                 real_denominator,
                                 imaginary_numerator,
                                 imaginary_denominator) {}
  Numeric(const char *real_numerator, const char *real_denominator,
          const char *imaginary_numerator, const char *imaginary_denominator)
      : internal_representation_(real_numerator,
                                 real_denominator,
                                 imaginary_numerator,
                                 imaginary_denominator) {}
  explicit Numeric(Numeric &&to_move)
      : internal_representation_(std::move(to_move.internal_representation_)) {}
  Numeric(const Numeric &to_copy) : internal_representation_(to_copy.internal_representation_) {}
  FORCE_INLINE std::string str() {
    return internal_representation_.str();
  }
  friend std::ostream &operator<<(std::ostream &os, const Numeric &num);
  friend std::ostream &operator<<(std::ostream &os, const Numeric &&num);
  ExtendedNumericType type() {
    if (internal_representation_.isFixnum()) { return fixnum; }
    else {
      return internal_representation_.extended_numeric_->type_;
    }
  }

//  FORCE INLINE Numeric operator+(const Numeric &right) {
//    bool this_is_fixnum = this->internal_representation_.isFixnum();
//    bool right_is_fixnum = right.internal_representation_.isFixnum();
//    if (this_is_fixnum) {
//      int64_t this_as_fixnum = this->internal_representation_.asFixnum();
//      if (right_is_fixnum) {
//        int64_t right_as_fixnum = right.internal_representation_.asFixnum();
//        int64_t result;
//        if (added_without_fixnum_overflow(this_as_fixnum, right_as_fixnum, result)) { return Numeric(result); }
//        else {
//          return Numeric(static_cast<cpp_int>(cpp_int(this_as_fixnum) + right_as_fixnum));
//        }
//      } else {
//        return Numeric(this_as_fixnum + *right.internal_representation_.extended_numeric_);
//      }
//    } else {
//      if (right_is_fixnum) {
//        return Numeric(*this->internal_representation_.extended_numeric_ + right.internal_representation_.asFixnum());
//      } else {
//        return Numeric(
//            *this->internal_representation_.extended_numeric_ + *right.internal_representation_.extended_numeric_);
//      }
//    }
//  }

#define INLINED_NUMERIC_OPERATION(BINARY_OP, FIXNUM_OP_WITHOUT_OVERFLOW, INTERMEDIATE_TYPE_ON_FAILURE) \
FORCE_INLINE Numeric operator BINARY_OP(const Numeric &right) {\
  bool this_is_fixnum = this->internal_representation_.isFixnum();\
  bool right_is_fixnum = right.internal_representation_.isFixnum();\
  if (this_is_fixnum) {\
    int64_t this_as_fixnum = this->internal_representation_.asFixnum();\
    if (right_is_fixnum) {\
      int64_t right_as_fixnum = right.internal_representation_.asFixnum();\
      int64_t result;\
      if (FIXNUM_OP_WITHOUT_OVERFLOW(this_as_fixnum, right_as_fixnum, result)) { return Numeric(result); }\
      else {\
        return Numeric(static_cast<INTERMEDIATE_TYPE_ON_FAILURE>(INTERMEDIATE_TYPE_ON_FAILURE(this_as_fixnum) BINARY_OP right_as_fixnum));\
      }\
    } else {\
      return Numeric(this_as_fixnum BINARY_OP *right.internal_representation_.extended_numeric_);\
    }\
  } else {\
    if (right_is_fixnum) {\
      return Numeric(*this->internal_representation_.extended_numeric_ BINARY_OP right.internal_representation_.asFixnum());\
    } else {\
      return Numeric(\
          *this->internal_representation_.extended_numeric_ BINARY_OP *right.internal_representation_.extended_numeric_);\
    }\
  }\
}

INLINED_NUMERIC_OPERATION(+, added_without_fixnum_overflow, cpp_int)
INLINED_NUMERIC_OPERATION(-, subtracted_without_fixnum_overflow, cpp_int)
INLINED_NUMERIC_OPERATION(*, multiplied_without_fixnum_overflow, cpp_int)
INLINED_NUMERIC_OPERATION(/, divided_without_fixnum_overflow_or_precision_loss, cpp_rational)

//  INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_INTO_INT_64_T(+)
//  INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_INTO_INT_64_T(-)
//  INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_INTO_INT_128_T(*)
  friend Numeric operator+(int64_t left, const Numeric &right) {
    return Numeric(left) + right;
  }
  friend Numeric operator-(int64_t left, const Numeric &right) {
    return Numeric(left) - right;
  }
  friend Numeric operator*(int64_t left, const Numeric &right) {
    return Numeric(left) * right;
  }
  friend Numeric operator/(int64_t left, const Numeric &right) {
    return Numeric(left) / right;
  }

//  INLINED_NUMERIC_OPERATION_WHERE_FIXNUM_RESULT_FITS_IN_FIXNUM(/)
  bool operator==(const Numeric &right) const;
  bool operator<(const Numeric &right) const;
  explicit operator int64_t() const {
    if (internal_representation_.isFixnum()) {
      return internal_representation_.asFixnum();
    } else {
      // TODO add explicit conversions for extended numerics
      return 0;
    }
  }
 private:
  NumericInternal internal_representation_;
};

#endif //WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_

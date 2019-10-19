//
// Created by scott on 9/28/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_
#define WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
#include "boost/multiprecision/cpp_int.hpp"
#include "util.hpp"

#define MAX_FIXNUM_VALUE 4611686018427387903
#define MIN_FIXNUM_VALUE -4611686018427387904

#define PTR_RETURN_NUM_OP_DECL(OP_SYMBOL, RETURN_TYPE, ARG_TYPE)\
virtual const RETURN_TYPE *operator OP_SYMBOL(const ARG_TYPE &right) const

#define NUM_COMP_DECL(OP_SYMBOL, ARG_TYPE)\
virtual bool operator OP_SYMBOL(const ARG_TYPE &right) const

#define INEQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(OP_SYMBOL)\
NUM_COMP_DECL(OP_SYMBOL, int64_t);\
NUM_COMP_DECL(OP_SYMBOL, ExtendedNumerics);\
NUM_COMP_DECL(OP_SYMBOL, BignumInternal);\
NUM_COMP_DECL(OP_SYMBOL, RatnumInternal);

#define EQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(OP_SYMBOL)\
INEQUALITY_COMPARISON_DECLARATIONS_WITH_EXTENDED_NUMERICS_FOR_OP(OP_SYMBOL)\
NUM_COMP_DECL(OP_SYMBOL, ExactComplexnumInternal);\
NUM_COMP_DECL(OP_SYMBOL, InexactComplexnumInternal);

#define DELETE_COPY_AND_MOVE_CONSTRUCTORS(CLASS)\
  CLASS(CLASS const &) = delete;\
  CLASS(CLASS&&) = delete;

typedef boost::multiprecision::cpp_rational cpp_rational;
typedef boost::multiprecision::cpp_int cpp_int;

enum ExtendedNumericType {
  bignum,
  ratnum,
  exact_complexnum,
  inexact_complexnum
};

class BignumInternal;
class RatnumInternal;
class ExactComplexnumInternal;
class InexactComplexnumInternal;
class Numeric;

class ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const ExtendedNumerics &num);
 public:
  ExtendedNumericType type_;
  DELETE_COPY_AND_MOVE_CONSTRUCTORS(ExtendedNumerics)
  virtual ~ExtendedNumerics() = default;

#define DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_TYPE(TYPE)\
  PTR_RETURN_NUM_OP_DECL(+, ExtendedNumerics, TYPE);\
  PTR_RETURN_NUM_OP_DECL(-, ExtendedNumerics, TYPE);\
  PTR_RETURN_NUM_OP_DECL(*, ExtendedNumerics, TYPE);\
  PTR_RETURN_NUM_OP_DECL(/, ExtendedNumerics, TYPE);\
  NUM_COMP_DECL(<, TYPE);\
  NUM_COMP_DECL(==, TYPE);\
  NUM_COMP_DECL(!=, TYPE);

  DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_TYPE(int64_t)
  DECLARE_EXTENDED_NUMERICS_OPERATORS_FOR_TYPE(ExtendedNumerics)
 protected:
  explicit ExtendedNumerics(ExtendedNumericType type) : type_(type) {}
};

class BignumInternal : public ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const BignumInternal &num);
  friend class RatnumInternal;
  friend class ExactComplexnumInternal;
  friend class InexactComplexnumInternal;
 public:
  DELETE_COPY_AND_MOVE_CONSTRUCTORS(BignumInternal)
  explicit BignumInternal(const char *digits) : ExtendedNumerics(bignum), internal_representation_(digits) {}
  explicit BignumInternal(const std::string &digits)
      : BignumInternal(digits.c_str()) {}
  explicit BignumInternal(cpp_int &&int_rep) noexcept : ExtendedNumerics(bignum), internal_representation_(std::move(int_rep)) {}

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
  friend std::ostream &operator<<(std::ostream &os, const RatnumInternal &num);
  friend class BignumInternal;
  friend class ExactComplexnumInternal;
  friend class InexactComplexnumInternal;
 public:
  DELETE_COPY_AND_MOVE_CONSTRUCTORS(RatnumInternal)
  RatnumInternal(const char *numerator, const char *denominator)
      : ExtendedNumerics(ratnum),
        internal_representation_(cpp_int(numerator), cpp_int(denominator)) {}
  RatnumInternal(const std::string &numerator, const std::string &denominator)
      : RatnumInternal(numerator.c_str(), denominator.c_str()) {}
  explicit RatnumInternal(cpp_rational &&int_rep) : ExtendedNumerics(ratnum), internal_representation_(std::move(int_rep)) {}

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
  friend class BignumInternal;
  friend class RatnumInternal;
  friend class InexactComplexnumInternal;
 public:
  DELETE_COPY_AND_MOVE_CONSTRUCTORS(ExactComplexnumInternal)
  ExactComplexnumInternal(const std::string &real_numerator,
                          const std::string &real_denominator,
                          const std::string &imaginary_numerator,
                          const std::string &imaginary_denominator)
      : ExtendedNumerics(exact_complexnum),
        real_(cpp_int(real_numerator), cpp_int(real_denominator)),
        imaginary_(cpp_int(imaginary_numerator), cpp_int(imaginary_denominator)) {}
  ExactComplexnumInternal(cpp_rational &&real, cpp_rational &&imaginary)
      : ExtendedNumerics(exact_complexnum),
        real_(std::move(real)),
        imaginary_(std::move(imaginary)) {}

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
  friend class BignumInternal;
  friend class RatnumInternal;
  friend class ExactComplexnumInternal;
 public:
  DELETE_COPY_AND_MOVE_CONSTRUCTORS(InexactComplexnumInternal)
  InexactComplexnumInternal(double real, double imaginary)
      : ExtendedNumerics(inexact_complexnum), real_(real), imaginary_(imaginary) {}

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
  int64_t fixnum_;
  const ExtendedNumerics *extended_numeric_;
  inline bool isFixnum() const { return static_cast<uint64_t>(fixnum_) & 1u; }
  inline int64_t asFixnum() const { return fixnum_ >> 1u; }
  ~NumericInternal() { if (!isFixnum()) { delete extended_numeric_; }}

  explicit NumericInternal(int64_t num) : fixnum_((num << 1u) | 1u) {}
  explicit NumericInternal(const ExtendedNumerics *num) : extended_numeric_(num) {}
  explicit NumericInternal(const std::string &digits);
  NumericInternal(double real, double imaginary)
      : extended_numeric_(new InexactComplexnumInternal(real, imaginary)) {}
  NumericInternal(const std::string &numerator, const std::string &denominator)
      : extended_numeric_(new RatnumInternal(numerator, denominator)) {}
  NumericInternal(const std::string &real_numerator,
                  const std::string &real_denominator,
                  const std::string &imaginary_numerator,
                  const std::string &imaginary_denominator)
      : extended_numeric_(new ExactComplexnumInternal(real_numerator,
                                                      real_denominator,
                                                      imaginary_numerator,
                                                      imaginary_denominator)) {};
};

class Numeric {
 public:
  explicit Numeric(int64_t num) : internal_representation_(num) {}
  explicit Numeric(const ExtendedNumerics *num) : internal_representation_(num) {}
  explicit Numeric(const std::string &digits) : internal_representation_(digits) {}
  Numeric(double real, double imaginary) : internal_representation_(real, imaginary) {}
  Numeric(const std::string &numerator, const std::string &denominator)
      : internal_representation_(numerator, denominator) {}
  Numeric(const std::string &real_numerator, const std::string &real_denominator,
          const std::string &imaginary_numerator, const std::string &imaginary_denominator)
      : internal_representation_(real_numerator,
                                 real_denominator,
                                 imaginary_numerator,
                                 imaginary_denominator) {}
  friend std::ostream &operator<<(std::ostream &os, Numeric &num);
  friend std::ostream &operator<<(std::ostream &os, Numeric &&num);
  Numeric operator+(const Numeric &right) const;
 private:
  NumericInternal internal_representation_;
};

#endif //WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_

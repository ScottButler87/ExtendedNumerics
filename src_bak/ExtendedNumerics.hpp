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
#include "NumericOperations.h"
#include "boost/multiprecision/cpp_int.hpp"

typedef boost::multiprecision::cpp_rational cpp_rational;
typedef boost::multiprecision::cpp_int cpp_int;

enum ExtendedNumericType {
  type_fixnum,
  bignum,
  ratnum,
};


class ExtendedNumerics {
 public:
  ExtendedNumerics(ExtendedNumericType type) {
    this->type_ = type;
  }
  ExtendedNumericType type_;
};

class Bignum;
class Ratnum;
class ExactComplexnum;
class InexactComplexnum;

class BignumInternal : public ExtendedNumerics {
 public:
  BignumInternal(const char * digits) : ExtendedNumerics(bignum), internal_representation_(digits) {
    this->type_ = bignum;
  }

  std::unique_ptr<const BignumInternal> operator+(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ + fixnum;
    return std::make_unique<const BignumInternal>(std::move(result));
  }

  std::unique_ptr<const Bignum> operator-(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ - fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }

  std::unique_ptr<const Bignum> operator*(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ * fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }

  std::unique_ptr<const Bignum> operator/(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ / fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }
 private:
  cpp_int internal_representation_;
};

class Bignum : ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const Bignum &B);
  friend Ratnum;
 public:
  Bignum() noexcept;
  Bignum(const Bignum &o) = default;
  Bignum(const Bignum &o, bool is_negative) noexcept;
  Bignum(uint64_t, bool) noexcept;
  Bignum(std::vector<uint64_t> &digits, bool) noexcept;
  Bignum(Bignum &&other) noexcept = default;
  explicit Bignum(cpp_int &&op_result) noexcept;
  Bignum(std::vector<uint64_t> &&digits, bool is_negative) noexcept;
  ~Bignum() = default;
  Bignum &operator=(Bignum &&right) = default;

  std::unique_ptr<const Bignum> operator+(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ + fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }

  std::unique_ptr<const Bignum> operator-(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ - fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }

  std::unique_ptr<const Bignum> operator*(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ * fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }

  std::unique_ptr<const Bignum> operator/(const int64_t &fixnum) const {
    cpp_int result = this->internal_rep_ / fixnum;
    return std::make_unique<const Bignum>(std::move(result));
  }

  NUM_OP_DECL(+, Bignum, Bignum);
  NUM_OP_DECL(-, Bignum, Bignum);
  NUM_OP_DECL(*, Bignum, Bignum);
  NUM_OP_DECL(/, Ratnum, Bignum);

  NUM_OP_DECL(+, Ratnum, Ratnum);
  NUM_OP_DECL(-, Ratnum, Ratnum);
  NUM_OP_DECL(*, Ratnum, Ratnum);
  NUM_OP_DECL(/, Ratnum, Ratnum);

  NUM_COMP_DECL(==, Bignum);
  NUM_COMP_DECL(==, Ratnum);

  bool isNegative() const;
  bool isOne() const;
  bool isZero() const;
 private:
  boost::multiprecision::cpp_int internal_rep_;
};

class Ratnum {
  friend std::ostream &operator<<(std::ostream &os, const Ratnum &B);
  friend Bignum;
 public:
  Ratnum() noexcept;
  Ratnum(const Ratnum &o) = default;
  Ratnum(const Ratnum &o, bool is_negative) noexcept;
  Ratnum(uint64_t numerator, bool) noexcept;
  Ratnum(uint64_t numerator, uint64_t denominator, bool) noexcept;
  explicit Ratnum(cpp_int &&numerator) noexcept;
  Ratnum(Ratnum &&other) noexcept;
  explicit Ratnum(cpp_rational &&op_result) noexcept;
  Ratnum(cpp_int &&numerator, cpp_int &&denominator) noexcept;
  explicit Ratnum(const std::string &string_representation) noexcept;
  ~Ratnum() = default;
  Ratnum &operator=(Ratnum &&right) = default;

  std::unique_ptr<const Ratnum> operator+(const int64_t &fixnum) const {
    cpp_rational result = this->internal_rep_ + fixnum;
    return std::make_unique<const Ratnum>(std::move(result));
  }

  std::unique_ptr<const Ratnum> operator-(const int64_t &fixnum) const {
    cpp_rational result = this->internal_rep_ - fixnum;
    return std::make_unique<const Ratnum>(std::move(result));
  }

  std::unique_ptr<const Ratnum> operator*(const int64_t &fixnum) const {
    cpp_rational result = this->internal_rep_ * fixnum;
    return std::make_unique<const Ratnum>(std::move(result));
  }

  std::unique_ptr<const Ratnum> operator/(const int64_t &fixnum) const {
    cpp_rational result = this->internal_rep_ / fixnum;
    return std::make_unique<const Ratnum>(std::move(result));
  }

  NUM_OP_DECL(+, Ratnum, Bignum);
  NUM_OP_DECL(-, Ratnum, Bignum);
  NUM_OP_DECL(*, Ratnum, Bignum);
  NUM_OP_DECL(/, Ratnum, Bignum);

  NUM_OP_DECL(+, Ratnum, Ratnum);
  NUM_OP_DECL(-, Ratnum, Ratnum);
  NUM_OP_DECL(*, Ratnum, Ratnum);
  NUM_OP_DECL(/, Ratnum, Ratnum);

  NUM_COMP_DECL(==, Ratnum);
  NUM_COMP_DECL(==, Bignum);

  bool isNegative() const;
  bool isOne() const;
  bool isZero() const;
 private:
  boost::multiprecision::cpp_rational internal_rep_;
};

class Numeric {
 public:
  Numeric operator+(const Numeric& right) const;
 private:
  union NumericInternal {
    int64_t fixnum;
    double flonum;
  } internal_;
};

class ExtendedNumeric {
 public:
  ExtendedNumeric operator+(const Numeric& right) const;
  union {
    std::unique_ptr<Bignum> bignum;
    std::unique_ptr<Ratnum> ratnum;
    std::unique_ptr<
  };
};


class ExactNum {
 public:
  ExactNum() : internal_rep_((int64_t)0), internal_type_(type_fixnum) {};
  ExactNum(const ExactNum &o) = default;
  ExactNum(ExactNum &&o) = default;
  explicit ExactNum(const int64_t &source) noexcept;
  explicit ExactNum(std::unique_ptr<const Bignum> &&source) noexcept;
  explicit ExactNum(std::unique_ptr<const Ratnum> &&source) noexcept;
  ~ExactNum();

  ExactNum operator+(const ExactNum &right) const;
  ExactNum operator-(const ExactNum &right) const;
  ExactNum operator*(const ExactNum &right) const;
  ExactNum operator/(const ExactNum &right) const;

 private:
  union ExactNumInternal {
    ExactNumInternal(const ExactNumInternal& o) = default;
    explicit ExactNumInternal(int64_t val) : fixnum(val) {};
    explicit ExactNumInternal(const class Bignum * source_bignum) : bignum(source_bignum) {};
    explicit ExactNumInternal(const class Ratnum * source_ratnum) : ratnum(source_ratnum) {};
    int64_t fixnum;
    const class Bignum * bignum;
    const class Ratnum * ratnum;
  } internal_rep_;

  uint8_t internal_type_;
};

class ExactComplexnum {

};

class InexactComplexnum {

};

#endif //WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_

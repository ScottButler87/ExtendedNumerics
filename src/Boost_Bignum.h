// Copyright 2019 Scott Butler

#ifndef EXTENDEDNUMERICS_BIGNUM_H_
#define EXTENDEDNUMERICS_BIGNUM_H_

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
#include "NumericOperations.h"
#include "boost/multiprecision/cpp_int.hpp"

class Bignum {
 public:
  Bignum();
  Bignum(const Bignum &o) = default;
  Bignum(const Bignum &o, bool is_negative);
  Bignum(uint64_t, bool);
  Bignum(std::vector<uint64_t> &digits, bool);
  Bignum(Bignum &&other) noexcept;
  explicit Bignum(boost::multiprecision::cpp_int &&op_result) noexcept;
  Bignum(std::vector<uint64_t> &&digits, bool is_negative);
  ~Bignum() = default;
  Bignum &operator=(Bignum &&right) = default;

  NUM_OP_DECL(+, Bignum, Bignum);
  NUM_OP_DECL(-, Bignum, Bignum);
  NUM_OP_DECL(*, Bignum, Bignum);
  std::unique_ptr<const Bignum> operator/(const Bignum &right) const;
  NUM_COMP_DECL(==, Bignum);

  bool isNegative() const;
  bool isOne() const;
  bool isZero() const;
  boost::multiprecision::cpp_int internal_rep_;
};

#endif  // EXTENDEDNUMERICS_BIGNUM_H_

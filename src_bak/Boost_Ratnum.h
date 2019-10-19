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

typedef boost::multiprecision::cpp_int cpp_int;
typedef boost::multiprecision::cpp_rational cpp_rational;

class Ratnum {
 public:
  Ratnum();
  Ratnum(const Ratnum &o) = default;
  Ratnum(const Ratnum &o, bool is_negative);
  Ratnum(uint64_t, bool);
  explicit Ratnum(cpp_int &&numerator) noexcept;
  Ratnum(Ratnum &&other) noexcept;
  explicit Ratnum(cpp_rational &&op_result) noexcept;
  Ratnum(cpp_int &&numerator, cpp_int &&denominator);
  explicit Ratnum(const std::string &string_representation);
  ~Ratnum() = default;
  Ratnum &operator=(Ratnum &&right) = default;

  NUM_OP_DECL(+, Ratnum, Ratnum);
  NUM_OP_DECL(-, Ratnum, Ratnum);
  NUM_OP_DECL(*, Ratnum, Ratnum);
  NUM_OP_DECL(/, Ratnum, Ratnum);
  NUM_COMP_DECL(==, Ratnum);

  bool isNegative() const;
  bool isOne() const;
  bool isZero() const;
  boost::multiprecision::cpp_rational internal_rep_;
};

#endif  // EXTENDEDNUMERICS_BIGNUM_H_

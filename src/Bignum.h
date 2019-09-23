// Copyright 2019 Scott Butler

#ifndef EXTENDEDNUMERICS_BIGNUM_H_
#define EXTENDEDNUMERICS_BIGNUM_H_

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
#include "NumericOperations.h"

class Bignum {
 public:
  Bignum();
  Bignum(const Bignum &o) = default;
  Bignum(const Bignum &other, bool isNegative) noexcept;
  Bignum(uint64_t, bool);
  Bignum(std::vector<uint64_t> &digits, bool);
  Bignum(std::vector<uint64_t> &&digits, bool);
  Bignum(Bignum &&other) noexcept;
  ~Bignum() = default;
  Bignum &operator=(Bignum &&right) = default;

  NUM_OP_DECL(+, Bignum, Bignum);
  NUM_OP_DECL(-, Bignum, Bignum);
  NUM_COMP_DECL(==, Bignum);

//  const Bignum &operator*(const Number &right) const override;
//  std::unique_ptr<Number> operator/(const Number &right) const;
//  bool operator>=(const Number &right) const;
//  bool operator>(const Number &right) const;
//  bool operator<=(const Number &right) const;
//  bool operator<(const Number &right) const;
//  bool operator==(std::shared_ptr<const NumericOperations> right) const override;
//  bool operator!=(const Number &right) const;
  bool isZero() const;
  friend std::ostream &operator<<(std::ostream &output, const Bignum &B);
 private:
  [[nodiscard]] std::unique_ptr<Bignum> NewBignumWithCombinedMagnitude(const Bignum &sign_dictating_addend,
                                                                       const Bignum &addend) const;
  [[nodiscard]] std::unique_ptr<Bignum> NewBignumWithReducedMagnitude(const Bignum &reducee,
                                                                      const Bignum &reducer) const;
  [[nodiscard]] int64_t CompareMagnitude(const Bignum &left, const Bignum &right) const;
  void TrimLeadingZeros(Bignum &toTrim) const;
  std::vector<uint64_t> digits_;
  bool isNegative_;
};

#endif  // EXTENDEDNUMERICS_BIGNUM_H_

// Copyright 2019 Scott Butler

#ifndef EXTENDEDNUMERICS_BIGNUM_H_
#define EXTENDEDNUMERICS_BIGNUM_H_

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
#include "../Number.h"

class Bignum : public Number {
 public:
  Bignum();
  Bignum(const Bignum &o);
  Bignum(uint64_t, bool);
  Bignum(std::vector<uint64_t> &digits, bool);
  ~Bignum() = default;
  Bignum &operator=(const Number &right);

  std::unique_ptr<Number> operator+(const Number &right) const;
  std::unique_ptr<Number> operator-(const Number &right) const;
  std::unique_ptr<Number> operator*(const Number &right) const;
//  std::unique_ptr<Number> operator/(const Number &right) const;
//  bool operator>=(const Number &right) const;
//  bool operator>(const Number &right) const;
//  bool operator<=(const Number &right) const;
//  bool operator<(const Number &right) const;
  bool operator==(const Number &right) const;
//  bool operator!=(const Number &right) const;
  friend std::ostream &operator<<(std::ostream &output, const Bignum &B);
 private:
  [[nodiscard]] std::unique_ptr<Bignum> WithCombinedMagnitude(const Bignum &right) const;
  [[nodiscard]] std::unique_ptr<Bignum> WithReducedMagnitude(const Bignum &reducee, const Bignum &reducer) const;
  [[nodiscard]] int64_t CompareMagnitude(const Bignum &left, const Bignum &right) const;
  void TrimLeadingZeros(Bignum &toTrim) const;
  std::vector<uint64_t> digits_;
};

#endif  // EXTENDEDNUMERICS_BIGNUM_H_

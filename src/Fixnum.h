// Copyright 2019 Scott Butler

#ifndef WASMEXTENDEDNUMERICS_FIXNUM_H
#define WASMEXTENDEDNUMERICS_FIXNUM_H

#include "../Number.h"

class Fixnum : public Number {
 public:
  Fixnum();
  Fixnum(const Fixnum &o);
  Fixnum(int64_t value);
  std::unique_ptr<Number> operator+(const Number &right);
  std::unique_ptr<Number> operator-(const Number &right);
  std::unique_ptr<Number> operator*(const Number &right);
  std::unique_ptr<Number> operator/(const Number &right);
  bool operator>=(const Number &right);
  bool operator>(const Number &right);
  bool operator<=(const Number &right);
  bool operator<(const Number &right);
  bool operator==(const Number &right);
  bool operator!=(const Number &right);

  [[nodiscard]] inline int64_t value() const {
    return value_;
  };
 private:
  int64_t value_;
};

#endif //WASMEXTENDEDNUMERICS_FIXNUM_H

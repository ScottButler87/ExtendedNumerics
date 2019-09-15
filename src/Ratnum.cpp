// Copyright 2019 Scott Butler

#include "Ratnum.h"

class Ratnum : public Number {
 public:
  Number operator+(Number &right) override {
    return nullptr;
  }

  Number operator-(Number &right) override {
    return nullptr;
  };

  Number operator*(Number &right) override {
    return nullptr;
  };

  Number operator/(Number &right) override {
    return nullptr;
  };

 protected:
  NumericType numericType() override {
    return ratnum_t;
  }
};
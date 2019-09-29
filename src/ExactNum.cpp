//
// Created by scott on 9/28/19.
//

#include "ExtendedNumerics.hpp"

#define EXACT_NUM_OP(OPERATOR) OPERATOR

ExactNum::ExactNum(const int64_t &source) noexcept : internal_rep_(source), internal_type_(type_fixnum) {}

ExactNum::ExactNum(std::unique_ptr<const class Bignum> &&source) noexcept
    : internal_rep_(source.release()), internal_type_(type_bignum) {}

ExactNum::ExactNum(std::unique_ptr<const class Ratnum> &&source) noexcept
    : internal_rep_(source.release()), internal_type_(type_ratnum) {}

ExactNum::~ExactNum() {
  switch (this->internal_type_) {
    case type_bignum:delete internal_rep_.bignum;
      break;
    case type_ratnum:delete internal_rep_.ratnum;
      break;
  }
}

ExactNum ExactNum::operator+(const ExactNum &right) const {
  switch (this->internal_type_) {
    case type_fixnum:
      switch (right.internal_type_) {
        case type_fixnum: return ExactNum(this->internal_rep_.fixnum + right.internal_rep_.fixnum);
        case type_bignum: return ExactNum( *right.internal_rep_.bignum + this->internal_rep_.fixnum);
        case type_ratnum: return ExactNum(*right.internal_rep_.ratnum + this->internal_rep_.fixnum);
      }
      break;

    case type_bignum:
      switch (right.internal_type_) {
//        case type_fixnum: return ExactNum()

      }
      break;

    case type_ratnum:break;
  }
  return ExactNum();
}

//
// Created by scott on 9/21/19.
//

#ifndef NUMERIC_OPERATIONS_H_
#define NUMERIC_OPERATIONS_H_
#include <sstream>
#define VIRTUAL_NUM_OP(OP_NAME, TYPE_NAME) virtual std::unique_ptr<const NumericOperations> OP_NAME ## TYPE_NAME(std::shared_ptr<const NumericOperations> right) const = 0;
#define VIRTUAL_NUM_OP_FOR_ALL_TYPES(OP_NAME)                                                          \
  virtual std::unique_ptr<const NumericOperations> OP_NAME ## Fixnum(int64_t fixnum) const = 0;        \
  VIRTUAL_NUM_OP(OP_NAME, Bignum)                                                                      \
  VIRTUAL_NUM_OP(OP_NAME, Ratnum)                                                                      \
  VIRTUAL_NUM_OP(OP_NAME, InexactComplexnum)                                                           \
  VIRTUAL_NUM_OP(OP_NAME, ExactComplexnum)                                                             \
  VIRTUAL_NUM_OP(OP_NAME, Flonum)

#define NUM_OP_DECL(OP_SYMBOL, RETURN_TYPE, ARG_TYPE)\
std::unique_ptr<const RETURN_TYPE> operator OP_SYMBOL(const ARG_TYPE &right) const

#define NUM_COMP_DECL(OP_SYMBOL, ARG_TYPE)\
bool operator OP_SYMBOL(const ARG_TYPE &right) const



class NumericOperations {
 public:
  enum NumericType {
    bignum_t = 0,
    ratnum_t = 1,
    inexact_complexnum_t = 2,
    exact_complexnum_t = 3,
    flonum_t = 4
  };
  enum NumericOperation {
    add,
    subtract,
    multiply,
    divide,
    less_than,
    less_than_or_equal_to,
    equal_to,
    not_equal_to,
    greater_than_or_equal_to,
    greater_than
  };
  struct {
    NumericType numericType;
    // The sign of this Number, 1 for negative and 0 for positive.
    bool isNegative;
  } header_;
  virtual ~NumericOperations() = 0;
  NumericOperations &operator=(std::shared_ptr<const NumericOperations> right) = delete;

  virtual std::unique_ptr<const NumericOperations> operator+(int64_t fixnum_value) const = 0;
  virtual std::unique_ptr<const NumericOperations> operator-(int64_t fixnum_value) const = 0;

  virtual std::unique_ptr<const NumericOperations> operator+(std::shared_ptr<const NumericOperations> right) const = 0;
  virtual std::unique_ptr<const NumericOperations> operator-(std::shared_ptr<const NumericOperations> right) const = 0;

  VIRTUAL_NUM_OP_FOR_ALL_TYPES(add)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(subtract)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(multiply)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(divide)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(lessThan)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(lessLessThanOrEqualTo)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(equalTo)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(notEqualTo)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(greater_than_or_equal_to)
  VIRTUAL_NUM_OP_FOR_ALL_TYPES(greater_than)


//  virtual const Number &operator*(const Number &right) const = 0;
//  virtual std::unique_ptr<Number> operator/(const Number &right) const = 0;
//  virtual bool operator>=(const Number &right) const = 0;
//  virtual bool operator>(const Number &right) const = 0;
//  virtual bool operator<=(const Number &right) const = 0;
//  virtual bool operator<(const Number &right) const = 0;

  virtual bool operator==(std::shared_ptr<const NumericOperations> right) const = 0;
  virtual bool isZero() const = 0;

  [[nodiscard]] std::string numericTypeString() const {
    switch (this->header_.numericType) {
      case bignum_t:return "Bignum";
      case ratnum_t:return "Ratnum";
      case inexact_complexnum_t:return "Inexact Complexnum";
      case exact_complexnum_t:return "Exact Complexnum";
      case flonum_t:return "Flonum";
      default:std::ostringstream out;
        out << header_.numericType;
        return out.str();
    }
  }
 protected:
  NumericOperations(NumericType t, bool isNegative) : header_({t, isNegative}) {}
};

// TODO flesh these out
// class Flonum : public Number {
// public:
//    Flonum() {
//
//    }
// protected:
//    NumericType numericType() override {
//        return header.numericType;
//    }
// };
//
// class ExactComplexnum : public Number {
// public:
//
// protected:
//    NumericType numericType() override {
//        return exact_complexnum_t;
//    }
//
// private:
//    class Ratnum real;
//    class Ratnum complex;
// };
//
// class InexactComplexnum : public Number {
// public:
//
// protected:
//    NumericType numericType() override {
//        return inexact_complexnum_t;
//    }
// };

#endif // NUMERIC_OPERATIONS_H_

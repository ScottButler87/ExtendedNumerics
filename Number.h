// Copyright 2019 Scott Butler

#ifndef NUMBER_H_
#define NUMBER_H_

#include <cstdint>
#include <memory>
#include <sstream>
#include "ExtendedNumerics/Bignum.h"


class Number {
 public:
    enum NumericType {
        fixnum_t = 1,
        bignum_t = 2,
        ratnum_t = 4,
        inexact_complexnum_t = 8,
        exact_complexnum_t = 16,
        flonum_t = 32,
    };
    struct NumberHeader {
        uint8_t numericType;
        // The sign of this Number, 1 for negative and 0 for positive.
        uint8_t sign;
    };
    virtual std::unique_ptr<Number> operator +(const Number& right) const = 0;
    virtual std::unique_ptr<Number> operator -(const Number& right) const = 0;
    virtual std::unique_ptr<Number> operator *(const Number& right) const = 0;
    virtual std::unique_ptr<Number> operator /(const Number& right) const = 0;
    virtual bool operator >=(const Number& right) const = 0;
    virtual bool operator >(const Number& right) const = 0;
    virtual bool operator <=(const Number& right) const = 0;
    virtual bool operator <(const Number& right) const = 0;
    virtual bool operator ==(const Number& right) const = 0;
    virtual bool operator !=(const Number& right) const = 0;

    [[nodiscard]] inline uint8_t numericType() const {
        return this->header_.numericType;
    }

    [[nodiscard]] inline uint8_t isNegative() const {
        return this->header_.sign;
    }

    [[nodiscard]] std::string numericTypeString() const {
        switch (this->header_.numericType) {
            case fixnum_t:
                return "Fixnum";
            case bignum_t:
                return "Bignum";
            case ratnum_t:
                return "Ratnum";
            case inexact_complexnum_t:
                return "Inexact Complexnum";
            case exact_complexnum_t:
                return "Exact Complexnum";
            case flonum_t:
                return "Flonum";
            default:
                std::ostringstream out;
                out << numericType();
                return out.str();
        }
    }

 protected:
    explicit Number(NumericType numericType)
        : header_({ static_cast<uint8_t>(numericType), 0}) {};
    Number(const Number &o) = default;
    ~Number() = default;
    struct NumberHeader header_{};
 private:
};

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

#endif  // NUMBER_H_

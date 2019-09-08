// Copyright 2019 Scott Butler

#include "../ExtendedNumerics/Bignum.h"
#include "Fixnum.h"
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <sstream>

Bignum::Bignum()
    : Number(bignum_t),
        digits_(1) {}

Bignum::Bignum(const Bignum &o)
    : Number(dynamic_cast<const Number &>(o)),
        digits_(o.digits_) {}

Bignum::Bignum(std::vector<uint64_t>& digits)
    : Number(bignum_t),
        digits_(digits) {
    header_.sign = digits.back() >> 31u;
}

Bignum& Bignum::operator =(const Number& right) {
    if (dynamic_cast<const Bignum*>(&right) == this) {
        return *this;
    }

    switch (right.numericType()) {
        case bignum_t: {
            auto other_bignum = dynamic_cast<const Bignum&>(right);
            header_ = other_bignum.header_;
            digits_ = std::vector<uint64_t>(other_bignum.digits_);
            return *this;
        }
        case fixnum_t: {
            int64_t fixnum = dynamic_cast<const Fixnum&>(right).value();
            header_.sign = (uint64_t)fixnum >> 31u;
            digits_ = std::vector<uint64_t>(1);
            digits_.push_back(std::abs(fixnum));
            return *this;
        }
        default: {
            std::ostringstream what;
            what << "Conversion from " << right.numericTypeString();
            what << " to Bignum not allowed";
            throw std::invalid_argument(what.str());
        }
    }
}

std::unique_ptr<Bignum> Bignum::operator+(const Number& right) const {
    switch (right.numericType()) {
        case bignum_t: {
            if (isNegative() == right.isNegative()) {
                return CombineMagnitude(dynamic_cast<const Bignum &>(right));
            } else {

            }
        }
    }
}

std::unique_ptr<Bignum> Bignum::operator-(const Number& right) const {
    switch (right.numericType()) {
        case bignum_t: {
            if (isNegative() ^ right.isNegative()) {
                std::unique_ptr<Bignum> temp = CombineMagnitude(dynamic_cast<const Bignum &>(right));
                temp->header_.sign = !right.isNegative();
                return std::move(temp);
            } else {

            }
        }
    }
}

// Returns a Bignum with the same sign as this Bignum, where its magnitude is
// equal to the magnitude of this Bignum plus the magnitude of Bignum right.
std::unique_ptr<Bignum> Bignum::CombineMagnitude(const Bignum& right) const {
    std::unique_ptr<Bignum> sum = std::make_unique<Bignum>(*this);
    size_t greatest_n = std::max(right.digits_.size(), this->digits_.size());
    int8_t carry = 0;
    sum->digits_.reserve(greatest_n + 1);
    size_t i;
    for (i = 0; i < greatest_n; ++i) {
        sum->digits_[i] = sum->digits_[i] + right.digits_[i] + carry;
        carry = sum->digits_[i] <= right.digits_[i] ? 1 : 0;
    }
    sum->digits_[i] = carry;
    return std::move(sum);
}

// Returns a Bignum with the same sign as the reducee, where its magnitude has
// been reduced by the magnitude of the reducer.
std::unique_ptr<Bignum> Bignum::ReduceMagnitude(const Bignum& reducee, const Bignum& reducer) const {
    std::unique_ptr difference = std::make_unique<Bignum>(reducee);
    size_t greatest_n = reducee.digits_.size();
    int8_t carry = 0;
    size_t i;
    uint64_t temp;
    for (i = 0; i < greatest_n; ++i) {
        temp = difference->digits_[i];
        difference->digits_[i] -= reducer.digits_[i] - carry;
        carry = difference->digits_[i] >= temp ? -1 : 0;
    }
    if (carry != 0) {
        difference->digits_[i] += carry;
    }
    return std::move(difference);
}

int8_t Bignum::CompareMagnitude(const Bignum& left, const Bignum& right) const {
    uint64_t left_size = left.digits_.size();
    uint64_t right_size = right.digits_.size();
    return (left_size - right_size) || (left.digits_[left_size-1] - right.digits_[right_size-1]);
}

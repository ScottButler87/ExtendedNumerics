// Copyright 2019 Scott Butler

#include "Ratnum.h"

class Ratnum : public Number {
public:
    std::unique_ptr<Number> operator +(Number& right) override {
        return nullptr;
    }

    std::unique_ptr<Number> operator -(Number& right) override {
        return nullptr;
    };

    std::unique_ptr<Number> operator *(Number& right) override {
        return nullptr;
    };

    std::unique_ptr<Number> operator /(Number& right) override {
        return nullptr;
    };

protected:
    NumericType numericType() override {
        return ratnum_t;
    }
};
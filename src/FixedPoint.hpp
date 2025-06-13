#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include <iostream>
#include <utility>  
#include "DecimalNumber.hpp"
#include "../MyExceptions/DivisionByZero.hpp"
#include "../MyExceptions/FixedPointOutOfRange.hpp"

template <int WholeBits, int FractionBits>
class FixedPoint : public DecimalNumber {
private:
    static_assert((WholeBits + FractionBits == 16) ||
              (WholeBits + FractionBits == 32) ||
              (WholeBits + FractionBits == 64),
              "Only 16, 32, or 64 total bits are supported");


    int64_t rawValue;
    static const int64_t scale = 1 << FractionBits;

public:
    explicit FixedPoint(float value)
    {
        float maxValue = static_cast<float>((int64_t(1) << WholeBits) - 1);
        float minValue;
        if (WholeBits == 0) { 
            minValue = -1.0f; 
        } else { 
            minValue = -static_cast<float>(int64_t(1) << WholeBits); 
        }

        if (value >= maxValue + 1.0f || value < minValue)
            throw FixedPointOutOfRange();

        rawValue = static_cast<int64_t>(value * scale);
    }

    explicit FixedPoint(int raw) : rawValue(raw) {} 

    explicit FixedPoint(const FixedPoint& other) {
        rawValue = other.rawValue;
    }

    FixedPoint(FixedPoint&& other) noexcept {
        rawValue = other.rawValue;
        other.rawValue = 0;
    }

    float ToFloat() const override {
        return static_cast<float>(rawValue) / scale;
    }

    void Print() const override {
        std::cout << "Q" << WholeBits << "." << FractionBits << " = " << ToFloat() << std::endl;
    }

    DecimalNumber* operator+(const DecimalNumber& other) const override {
        float result = this->ToFloat() + other.ToFloat();
        return new FixedPoint<WholeBits, FractionBits>(result);
    }

    DecimalNumber* operator-(const DecimalNumber& other) const override {
        float result = this->ToFloat() - other.ToFloat();
        return new FixedPoint<WholeBits, FractionBits>(result);
    }

    DecimalNumber* operator*(const DecimalNumber& other) const override {
        float result = this->ToFloat() * other.ToFloat();
        return new FixedPoint<WholeBits, FractionBits>(result);
    }

    DecimalNumber* operator/(const DecimalNumber& other) const override {
        float divisor = other.ToFloat();
        if (divisor == 0.0f)
            throw DivisionByZero();

        float result = this->ToFloat() / divisor;
        return new FixedPoint<WholeBits, FractionBits>(result);
        }

    FixedPoint& operator=(const FixedPoint& other) noexcept {
        if (this != &other) {
           rawValue = other.rawValue;
        }
        return *this;
    }

};
#endif
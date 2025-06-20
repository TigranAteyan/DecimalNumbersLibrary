#ifndef FLOATPOINT_HPP
#define FLOATPOINT_HPP

#include "DecimalNumber.hpp"
#include "../MyExceptions/DivisionByZero.hpp"
#include <iostream>
#include <cstring>

class FloatPoint : public DecimalNumber
{
private:
    int bits;  

    static float bitsToFloat(int b) {
        float result;
        std::memcpy(&result, &b, sizeof(float));
        return result;
    }

    static int floatToBits(float f) {
        int b;
        std::memcpy(&b, &f, sizeof(float));
        return b;
    }

public:
    explicit FloatPoint(const float& val) {
        bits = floatToBits(val);
    }

    FloatPoint(const FloatPoint& other) : bits(other.bits) {}

    FloatPoint(FloatPoint&& other) noexcept : bits(other.bits) {
        other.bits = 0;
    }

    float GetValue() const { return bitsToFloat(bits); }

    float ToFloat() const override {
        return bitsToFloat(bits);
    }

    void Print() const override {
        std::cout << "Floating = " << ToFloat() << std::endl;
    }

    DecimalNumber* operator+(const DecimalNumber& other) const override {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        float result = bitsToFloat(this->bits) + bitsToFloat(rhs.bits);
        return new FloatPoint(result);
    }

    DecimalNumber* operator-(const DecimalNumber& other) const override {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        float result = bitsToFloat(this->bits) - bitsToFloat(rhs.bits);
        return new FloatPoint(result);
    }

    DecimalNumber* operator*(const DecimalNumber& other) const override {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        float result = bitsToFloat(this->bits) * bitsToFloat(rhs.bits);
        return new FloatPoint(result);
    }

    DecimalNumber* operator/(const DecimalNumber& other) const override {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        float divisor = bitsToFloat(rhs.bits);
        if (divisor == 0.0f)
            throw DivisionByZero();

        float result = bitsToFloat(this->bits) / divisor;
        return new FloatPoint(result);
    }
};

#endif

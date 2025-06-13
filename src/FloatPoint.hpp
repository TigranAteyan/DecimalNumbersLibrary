#ifndef FLOATPOINT_H
#define FLOATPOINT_H

#include <iostream>
#include <cstdint>
#include "DecimalNumber.hpp"
#include "../MyExceptions/DivisionByZero.hpp"

template <int FractionBits>
class FloatPoint : public DecimalNumber {
private:
    static const int64_t scale = int64_t(1) << FractionBits;
    int64_t rawValue;

    static FloatPoint fromRaw(int64_t raw) {
        FloatPoint temp(0.0f);
        temp.rawValue = raw;
        return temp;
    }

public:
    explicit FloatPoint(float value) {
        rawValue = static_cast<int64_t>(value * scale);
    }

    explicit FloatPoint(int raw) : rawValue(raw) {}

    FloatPoint(const FloatPoint& other) {
        rawValue = other.rawValue;
    }

    FloatPoint(FloatPoint&& other) noexcept {
        rawValue = other.rawValue;
        other.rawValue = 0;
    }

    float ToFloat() const override {
        return static_cast<float>(rawValue) / scale;
    }

    void Print() const override {
        std::cout << "F(" << FractionBits << ") = " << ToFloat() << std::endl;
    }

    DecimalNumber* operator+(const DecimalNumber& other) const override {
        const auto& rhs = static_cast<const FloatPoint&>(other);
        return new FloatPoint(fromRaw(this->rawValue + rhs.rawValue));
    }

    DecimalNumber* operator-(const DecimalNumber& other) const override {
        const auto& rhs = static_cast<const FloatPoint&>(other);
        return new FloatPoint(fromRaw(this->rawValue - rhs.rawValue));
    }

    DecimalNumber* operator*(const DecimalNumber& other) const override {
        const auto& rhs = static_cast<const FloatPoint&>(other);
        int64_t result = (this->rawValue * rhs.rawValue) / scale;
        return new FloatPoint(fromRaw(result));
    }

    DecimalNumber* operator/(const DecimalNumber& other) const override {
        const auto& rhs = static_cast<const FloatPoint&>(other);
        if (rhs.rawValue == 0)
            throw DivisionByZero();

        int64_t result = (this->rawValue * scale) / rhs.rawValue;
        return new FloatPoint(fromRaw(result));
    }

    FloatPoint& operator=(const FloatPoint& other) {
        if (this != &other) {
            rawValue = other.rawValue;
        }
        return *this;
    }
};

#endif

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
    static_assert(WholeBits + FractionBits <= 31, "Too many bits");
    static constexpr int scale = 1 << FractionBits;
    int rawValue;

    FixedPoint(int raw, bool) : rawValue(raw) {}

public:
    explicit FixedPoint(float value)
    {
        float maxValue = static_cast<float>((1 << WholeBits) - (1.0f / (1 << FractionBits)));
        float minValue;
        if (WholeBits == 0) {
            minValue = -1.0f;
        } else {
            minValue = -static_cast<float>(1 << WholeBits);
        }

        if (value > maxValue || value < minValue)
            throw FixedPointOutOfRange();

        rawValue = static_cast<int>(value * scale);
    }

    explicit FixedPoint(int raw) : rawValue(raw) {}

    template<int W2, int F2>
    explicit FixedPoint(const FixedPoint<W2, F2>& other) {
        if constexpr (F2 > FractionBits)
            rawValue = static_cast<int>(other.getRaw() >> (F2 - FractionBits));
        else
            rawValue = static_cast<int>(other.getRaw() << (FractionBits - F2));
    }

    template<int W2, int F2>
    explicit FixedPoint(FixedPoint<W2, F2>&& other) noexcept {
        if constexpr (F2 > FractionBits)
            rawValue = static_cast<int>(other.getRaw() >> (F2 - FractionBits));
        else
            rawValue = static_cast<int>(other.getRaw() << (FractionBits - F2));
    }

    FixedPoint(const FixedPoint&) = default;
    FixedPoint(FixedPoint&&) noexcept = default;
    FixedPoint& operator=(const FixedPoint&) = default;
    FixedPoint& operator=(FixedPoint&&) noexcept = default;

    int getRaw() const {
        return rawValue;
    }

    float ToFloat() const override {
        return static_cast<float>(rawValue) / scale;
    }

    void Print() const override {
        std::cout << "Q" << WholeBits << "." << FractionBits << " = " << ToFloat() << std::endl;
    }

    DecimalNumber* operator+(const DecimalNumber& other) const override {
        const FixedPoint& rhs = static_cast<const FixedPoint&>(other);
        int resultRaw = this->rawValue + rhs.rawValue;
        return new FixedPoint(resultRaw, true);
    }

    DecimalNumber* operator-(const DecimalNumber& other) const override {
        const FixedPoint& rhs = static_cast<const FixedPoint&>(other);
        int resultRaw = this->rawValue - rhs.rawValue;
        return new FixedPoint(resultRaw, true);
    }

    DecimalNumber* operator*(const DecimalNumber& other) const override {
        const FixedPoint& rhs = static_cast<const FixedPoint&>(other);
        long long product = static_cast<long long>(this->rawValue) * rhs.rawValue;
        int resultRaw = static_cast<int>(product >> FractionBits);
        return new FixedPoint(resultRaw, true);
    }

    DecimalNumber* operator/(const DecimalNumber& other) const override {
        const FixedPoint& rhs = static_cast<const FixedPoint&>(other);
        if (rhs.rawValue == 0)
            throw DivisionByZero();

        long long numerator = (static_cast<long long>(this->rawValue) << FractionBits);
        int resultRaw = static_cast<int>(numerator / rhs.rawValue);
        return new FixedPoint(resultRaw, true);
    }
};

#endif

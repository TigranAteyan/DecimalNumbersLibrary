#ifndef FLOATPOINT_HPP
#define FLOATPOINT_HPP

#include "DecimalNumber.hpp"
#include "../MyExceptions/DivisionByZero.hpp"
#include <iostream>
#include <string>
#include <numeric>

class FloatPoint : public DecimalNumber
{
private:
    int integerValue = 0;
    int decimalScale = 1;
    std::string originalInput;

    void parseValue(const std::string& input)
    {
        for (char ch : input)
        {
            if (ch >= '0' && ch <= '9')
            {
                integerValue = (integerValue * 10) + (ch - '0');
            }
            else if (ch == '.')
            {
                continue;
            }
            else
            {
                throw std::out_of_range("Invalid character in input string");
            }
        }
    }

    void computeScale(const std::string& input)
    {
        auto dotPos = input.find('.');
        if (dotPos != std::string::npos)
        {
            int digitsAfterDot = input.length() - dotPos - 1;
            for (int i = 0; i < digitsAfterDot; ++i)
                decimalScale *= 10;
        }
    }

    int getCommonScale(int scale1, int scale2) const
    {
        return std::lcm(scale1, scale2);
    }

public:
    FloatPoint() = default;

    explicit FloatPoint(const std::string& input) : integerValue(0), decimalScale(1), originalInput(input)
    {
        parseValue(input);
        computeScale(input);
    }

    FloatPoint(int rawValue, int scale) : integerValue(rawValue), decimalScale(scale) {}

    FloatPoint(const FloatPoint& other) = default;
    FloatPoint(FloatPoint&& other) noexcept = default;

    FloatPoint& operator=(const FloatPoint& other) = default;
    FloatPoint& operator=(FloatPoint&& other) noexcept = default;

    void Print() const override
    {
        std::cout << ToFloat() << std::endl;
    }

    int getRawValue() const { return integerValue; }
    int getScale() const { return decimalScale; }

    float ToFloat() const override
    {
        return static_cast<float>(integerValue) / decimalScale;
    }

    DecimalNumber* operator+(const DecimalNumber& other) const override
    {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        int commonScale = getCommonScale(decimalScale, rhs.decimalScale);
        int lhsAdjusted = (commonScale / decimalScale) * integerValue;
        int rhsAdjusted = (commonScale / rhs.decimalScale) * rhs.integerValue;
        return new FloatPoint(lhsAdjusted + rhsAdjusted, commonScale);
    }

    DecimalNumber* operator-(const DecimalNumber& other) const override
    {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        int commonScale = getCommonScale(decimalScale, rhs.decimalScale);
        int lhsAdjusted = (commonScale / decimalScale) * integerValue;
        int rhsAdjusted = (commonScale / rhs.decimalScale) * rhs.integerValue;
        return new FloatPoint(lhsAdjusted - rhsAdjusted, commonScale);
    }

    DecimalNumber* operator*(const DecimalNumber& other) const override
    {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        int newValue = integerValue * rhs.integerValue;
        int newScale = decimalScale * rhs.decimalScale;
        return new FloatPoint(newValue, newScale);
    }

    DecimalNumber* operator/(const DecimalNumber& other) const override
    {
        const FloatPoint& rhs = static_cast<const FloatPoint&>(other);
        if (rhs.integerValue == 0)
            throw DivisionByZero();

        int newValue = integerValue * rhs.decimalScale;
        int newScale = decimalScale * rhs.integerValue;
        return new FloatPoint(newValue, newScale);
    }
};

#endif

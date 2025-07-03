#ifndef DECIMALNUMBER_HPP
#define DECIMALNUMBER_HPP

class DecimalNumber
{
public:
    virtual ~DecimalNumber() = default;

    virtual void Print() const = 0;
    virtual DecimalNumber* operator+(const DecimalNumber& other) const = 0;
    virtual DecimalNumber* operator-(const DecimalNumber& other) const = 0;
    virtual DecimalNumber* operator*(const DecimalNumber& other) const = 0;
    virtual DecimalNumber* operator/(const DecimalNumber& other) const = 0;

    virtual float ToFloat() const = 0;
};

#endif

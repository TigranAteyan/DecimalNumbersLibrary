#ifndef DECIMALNUMBER_H
#define DECIMALNUMBER_H

class DecimalNumber {
public:
    virtual ~DecimalNumber() = default;
    virtual void Print() const = 0;
    virtual float ToFloat() const = 0;

    virtual DecimalNumber* operator+(const DecimalNumber& other) const = 0;
    virtual DecimalNumber* operator-(const DecimalNumber& other) const = 0;
    virtual DecimalNumber* operator*(const DecimalNumber& other) const = 0;
    virtual DecimalNumber* operator/(const DecimalNumber& other) const = 0;

};

#endif
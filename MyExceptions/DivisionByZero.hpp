#ifndef DIVISIONBYZERO_H
#define DIVISIONBYZERO_H
#include <exception>

class DivisionByZero : public std::exception {
public:
    const char* what() const noexcept override {
        return "Division by zero";
    }
};


#endif
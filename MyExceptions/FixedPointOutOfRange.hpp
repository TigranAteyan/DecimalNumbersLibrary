#ifndef FIXEDPOINTOUTOFRANGE_H
#define FIXEDPOINTOUTOFRANGE_H
#include <exception>

class FixedPointOutOfRange : public std::exception {
public:
    const char* what() const noexcept override {
        return "Value out of range for Q format!";
    }
};

#endif
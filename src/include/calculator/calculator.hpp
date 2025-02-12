#pragma once

#include <stdexcept>
#include <string>

namespace calculator {

class DivisionByZeroError : public std::runtime_error {
public:
    explicit DivisionByZeroError() : std::runtime_error("Division by zero is not allowed") {}
};

class Calculator {
public:
    // Basic arithmetic operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
};

} // namespace calculator 
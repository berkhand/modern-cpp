#include "calculator/calculator.hpp"
#include <cmath>
#include <limits>

namespace calculator {

double Calculator::add(double a, double b) {
    // Check for overflow
    if ((b > 0 && a > std::numeric_limits<double>::max() - b) ||
        (b < 0 && a < std::numeric_limits<double>::lowest() - b)) {
        throw std::overflow_error("Addition would cause overflow");
    }
    return a + b;
}

double Calculator::subtract(double a, double b) {
    // Check for overflow
    if ((b < 0 && a > std::numeric_limits<double>::max() + b) ||
        (b > 0 && a < std::numeric_limits<double>::lowest() + b)) {
        throw std::overflow_error("Subtraction would cause overflow");
    }
    return a - b;
}

double Calculator::multiply(double a, double b) {
    // Check for overflow
    if (b != 0 && std::abs(a) > std::numeric_limits<double>::max() / std::abs(b)) {
        throw std::overflow_error("Multiplication would cause overflow");
    }
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (std::abs(b) < std::numeric_limits<double>::epsilon()) {
        throw DivisionByZeroError();
    }
    return a / b;
}

} // namespace calculator 
#include <gtest/gtest.h>
#include "calculator/calculator.hpp"
#include <cmath>
#include <limits>
#include <iostream>

using namespace calculator;

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
};

TEST_F(CalculatorTest, Addition) {
    std::cout << "Testing addition with (2.0, 3.0)..." << std::endl;
    EXPECT_DOUBLE_EQ(calc.add(2.0, 3.0), 5.0) << "Failed to add 2.0 + 3.0";
    
    std::cout << "Testing addition with negative number (-2.0, 3.0)..." << std::endl;
    EXPECT_DOUBLE_EQ(calc.add(-2.0, 3.0), 1.0) << "Failed to add -2.0 + 3.0";
    
    std::cout << "Testing addition with zeros (0.0, 0.0)..." << std::endl;
    EXPECT_DOUBLE_EQ(calc.add(0.0, 0.0), 0.0) << "Failed to add 0.0 + 0.0";
}

TEST_F(CalculatorTest, Subtraction) {
    EXPECT_DOUBLE_EQ(calc.subtract(5.0, 3.0), 2.0);
    EXPECT_DOUBLE_EQ(calc.subtract(-2.0, 3.0), -5.0);
    EXPECT_DOUBLE_EQ(calc.subtract(0.0, 0.0), 0.0);
}

TEST_F(CalculatorTest, Multiplication) {
    EXPECT_DOUBLE_EQ(calc.multiply(2.0, 3.0), 6.0);
    EXPECT_DOUBLE_EQ(calc.multiply(-2.0, 3.0), -6.0);
    EXPECT_DOUBLE_EQ(calc.multiply(0.0, 5.0), 0.0);
}

TEST_F(CalculatorTest, Division) {
    EXPECT_DOUBLE_EQ(calc.divide(6.0, 2.0), 3.0);
    EXPECT_DOUBLE_EQ(calc.divide(-6.0, 2.0), -3.0);
    EXPECT_DOUBLE_EQ(calc.divide(0.0, 5.0), 0.0);
}

TEST_F(CalculatorTest, DivisionByZero) {
    EXPECT_THROW(calc.divide(5.0, 0.0), DivisionByZeroError);
} 
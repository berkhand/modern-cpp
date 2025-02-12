#include <gtest/gtest.h>
#include "calculator/calculator_service.hpp"

namespace calculator {
namespace testing {

class CalculatorServiceTest : public ::testing::Test {
protected:
    CalculatorServer server_;
};

TEST_F(CalculatorServiceTest, Addition) {
    CalculationRequest request;
    request.set_a(2.0);
    request.set_b(3.0);
    request.set_operation(CalculationRequest::ADD);

    auto response = server_.Calculate(request);

    EXPECT_TRUE(response.error().empty());
    EXPECT_DOUBLE_EQ(response.result(), 5.0);
}

TEST_F(CalculatorServiceTest, DivisionByZero) {
    CalculationRequest request;
    request.set_a(5.0);
    request.set_b(0.0);
    request.set_operation(CalculationRequest::DIVIDE);

    auto response = server_.Calculate(request);

    EXPECT_FALSE(response.error().empty());
}

} // namespace testing
} // namespace calculator

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
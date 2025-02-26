#include <gtest/gtest.h>
#include <cstdio>  // for printf
#include "calculator/calculator_service.hpp"
#include "calculator.pb.h"  // Add this for protobuf generated types

namespace calculator {
namespace testing {

class CalculatorServiceTest : public ::testing::Test {
protected:
    // Constructor to initialize server_ first
    CalculatorServiceTest() : server_() {
        printf("Server created\n");
    }

    void SetUp() override {
        printf("Starting server\n");
        server_.Start();  // Now safe to call Start()
    }

    void TearDown() override {
        printf("Stopping server\n");
        server_.Stop();
    }

    CalculatorServer server_;  // Member is constructed before SetUp() is called
};

// Basic operation tests
TEST_F(CalculatorServiceTest, Addition) {
    CalculationRequest request;
    request.set_a(2.0);
    request.set_b(3.0);
    request.set_operation(CalculationRequest::ADD);

    auto response = server_.Calculate(request);

    EXPECT_TRUE(response.error().empty());
    EXPECT_DOUBLE_EQ(response.result(), 5.0);
}

TEST_F(CalculatorServiceTest, Subtraction) {
    CalculationRequest request;
    request.set_a(5.0);
    request.set_b(3.0);
    request.set_operation(CalculationRequest::SUBTRACT);

    auto response = server_.Calculate(request);

    EXPECT_TRUE(response.error().empty());
    EXPECT_DOUBLE_EQ(response.result(), 2.0);
}

// Error handling tests
TEST_F(CalculatorServiceTest, DivisionByZero) {
    CalculationRequest request;
    request.set_a(5.0);
    request.set_b(0.0);
    request.set_operation(CalculationRequest::DIVIDE);

    auto response = server_.Calculate(request);

    EXPECT_FALSE(response.error().empty());
    EXPECT_STREQ(response.error().c_str(), "Division by zero is not allowed");
}

TEST_F(CalculatorServiceTest, InvalidOperation) {
    CalculationRequest request;
    request.set_a(5.0);
    request.set_b(2.0);
    request.set_operation(static_cast<CalculationRequest::Operation>(999)); // Invalid operation

    auto response = server_.Calculate(request);

    EXPECT_FALSE(response.error().empty());
    EXPECT_STREQ(response.error().c_str(), "Unknown operation");
}

// Protobuf serialization tests
TEST_F(CalculatorServiceTest, SerializationDeserialization) {
    // Create and serialize request
    CalculationRequest original_request;
    original_request.set_a(10.5);
    original_request.set_b(20.7);
    original_request.set_operation(CalculationRequest::MULTIPLY);

    std::string serialized;
    ASSERT_TRUE(original_request.SerializeToString(&serialized));

    // Deserialize and verify
    CalculationRequest deserialized_request;
    ASSERT_TRUE(deserialized_request.ParseFromString(serialized));

    EXPECT_DOUBLE_EQ(deserialized_request.a(), 10.5);
    EXPECT_DOUBLE_EQ(deserialized_request.b(), 20.7);
    EXPECT_EQ(deserialized_request.operation(), CalculationRequest::MULTIPLY);
}

// End-to-end test
TEST_F(CalculatorServiceTest, EndToEndTest) {
    // Server is already started in SetUp()
    
    std::vector<std::pair<CalculationRequest, double>> test_cases = {
        {{[]() {
            CalculationRequest r;
            r.set_a(10);
            r.set_b(5);
            r.set_operation(CalculationRequest::ADD);
            return r;
        }()}, 15.0},
        {{[]() {
            CalculationRequest r;
            r.set_a(10);
            r.set_b(5);
            r.set_operation(CalculationRequest::MULTIPLY);
            return r;
        }()}, 50.0}
    };

    for (const auto& [request, expected] : test_cases) {
        auto response = server_.Calculate(request);
        EXPECT_TRUE(response.error().empty());
        EXPECT_DOUBLE_EQ(response.result(), expected);
    }
    // Server will be stopped in TearDown()
}

TEST_F(CalculatorServiceTest, EnhancedEndToEndTest) {
    // Server is already started in SetUp()
    
    struct TestCase {
        double a;
        double b;
        CalculationRequest::Operation op;
        double expected_result;
        bool should_succeed;
        std::string expected_error;
    };

    std::vector<TestCase> test_cases = {
        // Success cases
        {10.0, 5.0, CalculationRequest::ADD, 15.0, true, ""},
        {10.0, 5.0, CalculationRequest::SUBTRACT, 5.0, true, ""},
        {10.0, 5.0, CalculationRequest::MULTIPLY, 50.0, true, ""},
        {10.0, 5.0, CalculationRequest::DIVIDE, 2.0, true, ""},
        
        // Error cases
        {10.0, 0.0, CalculationRequest::DIVIDE, 0.0, false, "Division by zero is not allowed"},
        {1.0, 1.0, static_cast<CalculationRequest::Operation>(999), 0.0, false, "Unknown operation"}
    };

    for (const auto& tc : test_cases) {
        CalculationRequest request;
        request.set_a(tc.a);
        request.set_b(tc.b);
        request.set_operation(tc.op);

        auto response = server_.Calculate(request);

        if (tc.should_succeed) {
            EXPECT_TRUE(response.error().empty()) 
                << "Operation should succeed but got error: " << response.error();
            EXPECT_DOUBLE_EQ(response.result(), tc.expected_result)
                << "Wrong result for operation " << tc.op;
        } else {
            EXPECT_FALSE(response.error().empty()) 
                << "Operation should fail but succeeded";
            EXPECT_STREQ(response.error().c_str(), tc.expected_error.c_str())
                << "Wrong error message";
        }
    }
    // Server will be stopped in TearDown()
}

// Add this test after the other tests
TEST_F(CalculatorServiceTest, AsyncCalculations) {
    // Create multiple requests
    std::vector<std::pair<CalculationRequest, std::future<CalculationResponse>>> async_requests;
    
    // Setup requests
    for (int i = 0; i < 5; ++i) {
        CalculationRequest request;
        request.set_a(i);
        request.set_b(2);
        request.set_operation(CalculationRequest::MULTIPLY);
        
        // Create promise and future
        std::promise<CalculationResponse> promise;
        auto future = promise.get_future();
        
        // Store request and future
        async_requests.emplace_back(request, std::move(future));
        
        // Launch async calculation
        std::thread([this, req = request, promise = std::move(promise)]() mutable {
            auto response = server_.Calculate(req);
            promise.set_value(std::move(response));
        }).detach();
    }
    
    // Collect and verify results
    for (size_t i = 0; i < async_requests.size(); ++i) {
        auto response = async_requests[i].second.get();
        EXPECT_TRUE(response.error().empty()) 
            << "Error in async calculation " << i;
        EXPECT_DOUBLE_EQ(response.result(), i * 2.0) 
            << "Wrong result for async calculation " << i;
    }
}

} // namespace testing
} // namespace calculator
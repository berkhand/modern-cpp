#include "calculator/calculator_service.hpp"
#include <iostream>

void printResult(const calculator::CalculationResponse& response) {
    if (response.error().empty()) {
        std::cout << "Result: " << response.result() << std::endl;
    } else {
        std::cout << "Error: " << response.error() << std::endl;
    }
}

int main() {
    calculator::CalculatorServer server;
    server.Start();

    // Test addition
    calculator::CalculationRequest add_request;
    add_request.set_a(10.5);
    add_request.set_b(20.7);
    add_request.set_operation(calculator::CalculationRequest::ADD);
    
    auto response = server.Calculate(add_request);
    std::cout << "10.5 + 20.7 = ";
    printResult(response);

    // Test division by zero
    calculator::CalculationRequest div_request;
    div_request.set_a(10.0);
    div_request.set_b(0.0);
    div_request.set_operation(calculator::CalculationRequest::DIVIDE);
    
    response = server.Calculate(div_request);
    std::cout << "10.0 / 0.0 = ";
    printResult(response);

    server.Stop();
    return 0;
} 
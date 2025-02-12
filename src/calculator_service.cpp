#include "calculator/calculator_service.hpp"
#include <stdexcept>

namespace calculator {

CalculatorService::CalculatorService() : calculator_() {}

CalculationResponse CalculatorService::Calculate(const CalculationRequest& request) {
    CalculationResponse response;
    
    try {
        switch (request.operation()) {
            case CalculationRequest::ADD:
                response.set_result(calculator_.add(request.a(), request.b()));
                break;
            case CalculationRequest::SUBTRACT:
                response.set_result(calculator_.subtract(request.a(), request.b()));
                break;
            case CalculationRequest::MULTIPLY:
                response.set_result(calculator_.multiply(request.a(), request.b()));
                break;
            case CalculationRequest::DIVIDE:
                response.set_result(calculator_.divide(request.a(), request.b()));
                break;
            default:
                response.set_error("Unknown operation");
        }
    } catch (const std::exception& e) {
        response.set_error(e.what());
    }
    
    return response;
}

} // namespace calculator 
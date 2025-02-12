#include "calculator/calculator_service.hpp"
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <csignal>    // for signal, SIGINT
#include <unistd.h>   // for pause()

namespace calculator {

CalculatorServer::CalculatorServer() : running_(false) {}

void CalculatorServer::Start() {
    running_ = true;
    worker_thread_ = std::thread(&CalculatorServer::ProcessRequests, this);
    std::cout << "Calculator server started" << std::endl;
}

void CalculatorServer::Stop() {
    running_ = false;
    condition_.notify_one();
    if (worker_thread_.joinable()) {
        worker_thread_.join();
    }
    std::cout << "Calculator server stopped" << std::endl;
}

CalculationResponse CalculatorServer::ProcessRequest(const CalculationRequest& request) {
    return service_.Calculate(request);
}

CalculationResponse CalculatorServer::Calculate(const CalculationRequest& request) {
    return ProcessRequest(request);
}

void CalculatorServer::ProcessRequests() {
    while (running_) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock);
    }
}

} // namespace calculator 
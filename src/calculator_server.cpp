#include "calculator/calculator_service.hpp"
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <csignal>    // for signal, SIGINT
#include <unistd.h>   // for pause()
#include <chrono>

namespace calculator {

CalculatorServer::CalculatorServer() : running_(false) {}

void CalculatorServer::Start() {
    running_ = true;
    worker_thread_ = std::thread(&CalculatorServer::ProcessRequests, this);
    std::cout << "Calculator server started" << std::endl;
}

void CalculatorServer::Stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        running_ = false;
    }
    condition_.notify_one();
    if (worker_thread_.joinable()) {
        worker_thread_.join();
    }
    std::cout << "Calculator server stopped" << std::endl;
}

CalculationResponse CalculatorServer::Calculate(const CalculationRequest& request) {
    // Create promise and future for the response
    std::promise<CalculationResponse> response_promise;
    auto response_future = response_promise.get_future();
    
    // Queue the request
    {
        std::lock_guard<std::mutex> lock(mutex_);
        request_queue_.push(QueuedRequest{request, std::move(response_promise)});
    }
    condition_.notify_one();
    
    // Wait for and return the response
    return response_future.get();
}

void CalculatorServer::ProcessRequests() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        // Wait for requests or check if should stop
        condition_.wait(lock, [this] {
            return !running_ || !request_queue_.empty();
        });

        // Check if we should stop
        if (!running_ && request_queue_.empty()) {
            break;
        }

        // Process all available requests
        while (!request_queue_.empty()) {
            auto request = std::move(request_queue_.front());
            request_queue_.pop();
            
            // Process request outside of lock
            lock.unlock();
            auto response = service_.Calculate(request.request);
            request.response_promise.set_value(std::move(response));
            lock.lock();
        }
    }
}

} // namespace calculator 
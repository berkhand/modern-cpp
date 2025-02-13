#pragma once

#include "calculator/calculator.hpp"
#include "calculator.pb.h"
#include <memory>
#include <thread>              // for std::thread
#include <mutex>              // for std::mutex
#include <condition_variable> // for std::condition_variable
#include <chrono>  // Add this for timeout
#include <queue>
#include <future>

namespace calculator {

class CalculatorService {
public:
    CalculatorService();
    CalculationResponse Calculate(const CalculationRequest& request);

private:
    Calculator calculator_;
};

class CalculatorServer {
public:
    CalculatorServer();
    void Start();
    void Stop();
    CalculationResponse Calculate(const CalculationRequest& request);

private:
    void ProcessRequests();
    
    struct QueuedRequest {
        CalculationRequest request;
        std::promise<CalculationResponse> response_promise;
    };

    CalculatorService service_;
    std::thread worker_thread_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<QueuedRequest> request_queue_;
    bool running_;
};

} // namespace calculator 
#include "calculator/calculator_service.hpp"
#include <iostream>
#include <csignal>
#include <unistd.h>

int main() {
    calculator::CalculatorServer server;
    server.Start();

    // Wait for Ctrl+C
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    std::signal(SIGINT, [](int) { std::cout << "\nShutting down..." << std::endl; });
    pause();

    server.Stop();
    return 0;
} 
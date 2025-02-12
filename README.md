# Modern C++ Calculator Project

A modern C++ calculator project demonstrating best practices in C++ development, including:
- Modern C++ features (C++17)
- CMake build system
- Conan package management
- Google Test framework
- Exception handling
- RAII principles

## Project Structure

```
modern-cpp-project/
├── src/
│   ├── include/
│   │   └── calculator/
│   │       └── calculator.hpp    # Calculator class declaration
│   └── calculator.cpp            # Calculator implementation
├── tests/
│   └── calculator_test.cpp       # Unit tests
├── conanfile.py                  # Conan package requirements
└── CMakeLists.txt               # CMake build configuration
```

## Prerequisites

- CMake (>= 3.15)
- Conan package manager
- C++17 compatible compiler
- Git

## Building the Project

1. Clone the repository:
```bash
git clone <repository-url>
cd modern-cpp-project
```

2. Create build directory and navigate to it:
```bash
mkdir build && cd build
```

3. Install dependencies using Conan:
```bash
conan install .. --output-folder=. --build=missing
```

4. Configure and build:
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Running Tests

After building, you can run the tests using:
```bash
# Run tests with detailed output
./calculator_test --gtest_color=yes
```

Or using CTest:
```bash
ctest --verbose
```

## Features

The calculator currently supports:
- Addition
- Subtraction
- Multiplication
- Division (with division by zero protection)
- Error handling for edge cases
- Comprehensive unit tests

## Development Stages

This project is being developed in multiple stages:

- [x] Stage 1: Core C++ Library
  - Basic arithmetic operations
  - Unit tests
  - CMake configuration
  - Conan integration

- [ ] Stage 2: gRPC Service Integration
- [ ] Stage 3: Android Native Library
- [ ] Stage 4: Android Application

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details. 
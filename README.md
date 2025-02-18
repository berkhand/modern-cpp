# Modern C++ Calculator Project

A modern C++ calculator project demonstrating protocol buffers, service architecture, and comprehensive testing strategies.

## Project Structure

```
.
├── src/
│   ├── include/
│   │   └── calculator/
│   │       ├── calculator.hpp
│   │       └── calculator_service.hpp
│   │   └── calculator.hpp    # Calculator class declaration
│   └── calculator.cpp            # Calculator implementation
├── tests/
│   ├── calculator_test.cpp
│   └── calculator_service_test.cpp
├── examples/
│   └── calculator_client.cpp
└── CMakeLists.txt
```

## Prerequisites

- CMake (>= 3.15)
- Conan package manager
- C++17 compatible compiler
- Git
- Protocol Buffers compiler (`protoc`)

## Setting Up the Environment

To avoid mixing Conan configurations with other projects, it is recommended to set the `CONAN_HOME` environment variable to a specific directory for this project. You can do this by running the following command:

```bash
export CONAN_HOME=/home/deniz/Projects/modern-cpp-project/.conan
```

To ensure this variable is set every time you work on this project, you can create a `conan.sh` script with the above line and source it in your terminal session:

```bash
source ./conan.sh
```

**Note**: Remember to call `source ./conan.sh` at the start of each new terminal session before running any Conan commands.

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
conan install -u . --install-folder=build -s build_type=Debug -pr linux_x86_64-clang6 --build=missing
```

4. Build the project using Conan:
```bash
conan build --configure --build --build-folder=build .
```

5. Alternatively, configure and build using CMake:
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Testing Strategy

The project includes comprehensive testing at multiple levels:

### 1. Unit Tests (calculator_test.cpp)
Tests the core calculator functionality:
- Basic arithmetic operations
- Error handling (e.g., division by zero)

### 2. Service Tests (calculator_service_test.cpp)
Tests the calculator service implementation with various scenarios:

#### Basic Operation Tests
```cpp
TEST_F(CalculatorServiceTest, Addition) {
    CalculationRequest request;
    request.set_a(2.0);
    request.set_b(3.0);
    request.set_operation(CalculationRequest::ADD);

    auto response = server_.Calculate(request);

    EXPECT_TRUE(response.error().empty());
    EXPECT_DOUBLE_EQ(response.result(), 5.0);
}
```

#### Protocol Buffer Serialization Tests
```cpp
TEST_F(CalculatorServiceTest, SerializationDeserialization) {
    CalculationRequest original_request;
    original_request.set_a(10.5);
    original_request.set_b(20.7);
    original_request.set_operation(CalculationRequest::MULTIPLY);

    std::string serialized;
    ASSERT_TRUE(original_request.SerializeToString(&serialized));

    CalculationRequest deserialized_request;
    ASSERT_TRUE(deserialized_request.ParseFromString(serialized));
    
    EXPECT_DOUBLE_EQ(deserialized_request.a(), 10.5);
}
```

#### End-to-End Tests
Tests complete workflows including server startup/shutdown:
```cpp
TEST_F(CalculatorServiceTest, EnhancedEndToEndTest) {
    server_.Start();

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
        // Error cases
        {10.0, 0.0, CalculationRequest::DIVIDE, 0.0, false, "Division by zero is not allowed"}
    };

    for (const auto& tc : test_cases) {
        // Process test cases...
    }

    server_.Stop();
}
```

## Running the Examples

### Calculator Client
```bash
# In build directory
./calculator_client
```

Example output:
```
Calculator server started
10.5 + 20.7 = Result: 31.2
10.0 / 0.0 = Error: Division by zero is not allowed
Calculator server stopped
```

### Running Tests
```bash
# Run all tests
ctest --output-on-failure

# Run specific test
./calculator_test
./calculator_service_test
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

## Useful Conan Commands

Here are some of the most useful Conan commands you may need while working on this project:

1. **Install Dependencies**:
   ```bash
   conan install -u . --install-folder=build -s build_type=Debug -pr linux_x86_64-clang6 --build=missing
   conan install . --install-folder=build -s build_type=Debug -pr linux_x86_64-clang6 --build=missing
   ```
   Installs the dependencies specified in the `conanfile.txt` or `conanfile.py`. The `--build=missing` flag builds any dependencies that are not available in the local cache.

2. **Build the Project**:
   ```bash
   conan build --configure --build --build-folder=build .
   ```
   Builds the project using the configuration specified in the `conanfile.py`.

3. **Create a Package**:
   ```bash
   conan create . user/channel
   ```
   Creates a package from the current directory. Replace `user/channel` with your desired user and channel.

4. **Upload a Package**:
   ```bash
   conan upload package_name/version@user/channel --all
   ```
   Uploads a package to a remote server. The `--all` flag uploads all package binaries.

5. **Search for Packages**:
   ```bash
   conan search "*"
   ```
   Searches for all packages in the local cache or remote servers.

6. **Show Profile Information**:
   ```bash
   conan profile show default
   ```
   Displays the details of the default profile, including settings and options.

7. **List Profiles**:
   ```bash
   conan profile list
   ```
   Lists all available profiles in the local cache.

8. **Display Package Information**:
   ```bash
   conan info ..
   ```
   Displays information about the current project and its dependencies.

9. **List Remotes**:
   ```bash
   conan remote list
   ```
   Lists all configured remotes for Conan.

10. **Remove Packages**:
    ```bash
    conan remove package_name/version@user/channel --force
    ```
    Removes a package from the local cache. The `--force` flag is used to bypass confirmation.

11. **Clear Entire Cache**:
    ```bash
    conan remove "*" --force
    ```
    Clears the entire Conan cache by removing all packages. Use with caution, as this will delete all cached packages.

12. **Update Dependencies**:
    ```bash
    conan install .. --update
    ```
    Updates the dependencies to the latest versions available in the remotes.

### Summary

This section provides a quick reference for common Conan commands that can help streamline your workflow while working on the project. 
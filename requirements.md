# Calculator App - Staged Development Requirements

## Stage 1: Core C++ Library Setup & Implementation

### 1.1 Project Structure Setup
```
modern-cpp-project/
├── src/
│   ├── include/
│   │   └── calculator/
│   │       └── calculator.hpp
│   └── calculator.cpp
├── tests/
│   └── calculator_test.cpp
├── conanfile.py
└── CMakeLists.txt
```

### 1.2 Core Library Requirements
calculator.hpp:
```cpp
class Calculator {
    // Basic operations with modern C++ features
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
};
```

Key features:
- Modern C++ (17/20) features
- Exception handling
- Input validation
- RAII principles

### 1.3 Build System
```cmake
# CMake configuration
- C++17 support
- Conan package management
- GTest integration
- fmt library
```

### 1.4 Test Criteria
- Build successfully completes
- All unit tests pass
- No memory leaks
- Error cases handled correctly

## Stage 2: gRPC Service Integration

### 2.1 Add gRPC Structure
```
modern-cpp-project/
├── src/
│   ├── protos/
│   │   └── calculator.proto
│   └── calculator_service.cpp
└── tests/
    └── calculator_service_test.cpp
```

### 2.2 Service Requirements
calculator.proto:
```protobuf
service CalculatorService {
    rpc Calculate(CalculatorRequest) returns (CalculatorResponse);
}
```

Features:
- Basic RPC operations
- Error handling
- Request/Response types
- Service implementation

### 2.3 Test Criteria
- Service starts successfully
- Can handle client requests
- Error cases managed
- Performance metrics acceptable

## Stage 3: Android Native Library

### 3.1 Android Library Structure
```
modern-cpp-project/
└── android/
    └── calculator-lib/
        ├── src/
        │   └── main/
        │       ├── cpp/
        │       │   ├── calculator_jni.cpp
        │       │   └── calculator_jni.h
        │       └── java/
        │           └── Calculator.java
        ├── build.gradle
        └── CMakeLists.txt
```

### 3.2 Library Requirements
- JNI wrapper for C++ code
- Java API for Android
- Error handling
- Resource management

### 3.3 Test Criteria
- Library builds successfully
- JNI calls work correctly
- Memory management is proper
- Java API is user-friendly

## Stage 4: Android Application

### 4.1 App Structure
```
modern-cpp-project/
└── android/
    └── app/
        └── src/
            └── main/
                ├── java/
                │   └── MainActivity.kt
                └── res/
                    └── layout/
                        └── activity_main.xml
```

### 4.2 App Requirements
- Material Design UI
- gRPC client integration
- Error state handling
- Result display
- Loading states

### 4.3 Test Criteria
- App runs without crashes
- UI is responsive
- Network errors handled
- Good user experience

## Testing Instructions for Each Stage

### Stage 1 Testing:
```bash
# Build and test core library
mkdir build && cd build
conan install ..
cmake ..
make
./calculator_test
```

Expected results:
- All tests pass
- No memory leaks in valgrind
- Clean build output

### Stage 2 Testing:
```bash
# Test gRPC service
./calculator_service &
grpcurl -d '{"a": 5, "b": 3}' localhost:50051 calculator.Calculate
```

Expected results:
- Service responds correctly
- Error cases handled gracefully
- Performance within limits

### Stage 3 Testing:
```bash
# Build Android library
cd android/calculator-lib
./gradlew build
```

Expected results:
- Library builds successfully
- Unit tests pass
- No JNI errors

### Stage 4 Testing:
```bash
# Run Android app
cd android/app
./gradlew installDebug
```

Expected results:
- App installs and runs
- Can perform calculations
- UI works smoothly

## Development Flow for Each Stage

### Stage 1:
1. Set up project structure
2. Implement calculator.hpp
3. Implement calculator.cpp
4. Write unit tests
5. Set up build system
6. Test and verify

### Stage 2:
1. Define proto file
2. Implement service
3. Add service tests
4. Test with mock client
5. Performance testing

### Stage 3:
1. Create JNI wrapper
2. Implement Java API
3. Set up Android build
4. Test native bridge

### Stage 4:
1. Create UI layout
2. Implement ViewModel
3. Add gRPC client
4. End-to-end testing

## Success Criteria for Each Stage

### Stage 1:
- [ ] Builds without errors
- [ ] All unit tests pass
- [ ] Memory checks clean
- [ ] Documentation complete

### Stage 2:
- [ ] Service runs stable
- [ ] RPC calls work
- [ ] Error handling works
- [ ] Performance acceptable

### Stage 3:
- [ ] Library builds
- [ ] JNI works correctly
- [ ] Java API complete
- [ ] Tests pass

### Stage 4:
- [ ] App runs smooth
- [ ] UI responsive
- [ ] Network handling works
- [ ] Good user experience

## Notes for Cursor
- Implement one stage at a time
- Follow modern C++ practices
- Add detailed comments
- Include error handling
- Write comprehensive tests
- Focus on code quality
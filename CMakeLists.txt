cmake_minimum_required(VERSION 3.15)
project(calculator-app VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Find dependencies
find_package(GTest REQUIRED)
find_package(fmt REQUIRED)

# Create calculator library
add_library(calculator
    src/calculator.cpp
)

target_include_directories(calculator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_link_libraries(calculator
    PUBLIC
        fmt::fmt
)

# Create tests
add_executable(calculator_test
    tests/calculator_test.cpp
)

target_include_directories(calculator_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        $<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(calculator_test
    PRIVATE
        calculator
        GTest::gtest
        GTest::gtest_main
)

# Add test with labels
add_test(
    NAME calculator_test 
    COMMAND calculator_test --gtest_output=xml:test_results.xml
) 
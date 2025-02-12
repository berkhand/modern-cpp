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
find_package(Protobuf CONFIG REQUIRED)

# After find_package commands, add:
include_directories(${Protobuf_INCLUDE_DIRS})

# Create calculator library
add_library(calculator
    src/calculator.cpp
)

target_include_directories(calculator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
        ${Protobuf_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS_PROTOBUF}
)

target_link_libraries(calculator
    PUBLIC
        fmt::fmt
        protobuf::libprotobuf
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

# Create directory for generated files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Generate protobuf files
execute_process(
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/generated
    -I=${CMAKE_CURRENT_SOURCE_DIR}/src/protos
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protos/calculator.proto
    RESULT_VARIABLE PROTOC_RESULT
)

if(NOT PROTOC_RESULT EQUAL 0)
    message(FATAL_ERROR "Error generating protobuf code from proto file")
endif()

# Add calculator_service.cpp to calculator library
target_sources(calculator
    PRIVATE
        src/calculator.cpp
        src/calculator_service.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/generated/calculator.pb.cc
)

# First, create a library for the server implementation
add_library(calculator_server_lib
    src/calculator_server.cpp
)

target_link_libraries(calculator_server_lib
    PUBLIC
        calculator
        protobuf::libprotobuf
)

# Update the server executable to use the library
add_executable(calculator_server
    src/calculator_server_main.cpp  # Rename the main function to a new file
)

target_link_libraries(calculator_server
    PRIVATE
        calculator_server_lib
)

# Update the service test to link with the server library
add_executable(calculator_service_test
    tests/calculator_service_test.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/calculator.pb.cc
)

target_link_libraries(calculator_service_test
    PRIVATE
        calculator_server_lib
        GTest::gtest
        GTest::gtest_main
)

add_test(
    NAME calculator_service_test
    COMMAND calculator_service_test
)

# Update server include paths
target_include_directories(calculator_server
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
        ${Protobuf_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS_PROTOBUF}
)

# Update service test include paths
target_include_directories(calculator_service_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
        ${Protobuf_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS_PROTOBUF}
        $<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES>
) 
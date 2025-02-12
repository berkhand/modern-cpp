from conan import ConanFile
from conan.tools.cmake import CMake

class CalculatorAppRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("gtest/cci.20210126")
        self.requires("fmt/8.1.1")
        self.requires("protobuf/3.17.1")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build() 
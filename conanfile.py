from conan import ConanFile
from conan.tools.cmake import CMake
from multiprocessing import cpu_count

class CalculatorAppRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("gtest/[>=1.15.2]")
        self.requires("fmt/[>=10.2.1]")
        self.requires("protobuf/[>=3.19.1]")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build() 

        # Run tests as part of build
        self.run(
            f"ctest --build-config {self.settings.build_type} -j {cpu_count()} --output-on-failure",
            run_environment=True,
        )
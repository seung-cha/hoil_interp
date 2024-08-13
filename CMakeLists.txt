cmake_minimum_required(VERSION 3.8)
project(Toylan LANGUAGES CXX)

#enable testing
include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_library(lib STATIC src/scanner.cpp src/lexer.cpp)

add_executable(Toylan src/main.cpp)
target_link_libraries(Toylan PUBLIC lib)

add_test(TEST_0, "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}" "test/lexer/test0")


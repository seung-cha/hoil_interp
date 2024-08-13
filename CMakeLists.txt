cmake_minimum_required(VERSION 3.8)
project(Toylan LANGUAGES CXX)

#enable testing
include(CTest)
enable_testing()

# set CPP standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(src)
add_subdirectory(test)

add_executable("${PROJECT_NAME}" src/main.cpp)
target_link_libraries("${PROJECT_NAME}" PUBLIC Lib)

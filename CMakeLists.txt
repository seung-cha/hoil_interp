cmake_minimum_required(VERSION 3.10)

project(Toylan)


add_executable(Toylan 
            "${PROJECT_SOURCE_DIR}/src/main.cpp"
            "${PROJECT_SOURCE_DIR}/src/scanner.cpp"
            "${PROJECT_SOURCE_DIR}/src/lexer.cpp")

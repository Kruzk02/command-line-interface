cmake_minimum_required(VERSION 3.28.3)
project("cli")

add_executable(${PROJECT_NAME} ./src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23
                                                 CXX_STANDARD_REQUIRED YES)

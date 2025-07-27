cmake_minimum_required(VERSION 3.28.3)
project("cli")

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23 D_REQUIRED YES)

cmake_minimum_required(VERSION 3.28)
project(cli)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23
                                                 CXX_STANDARD_REQUIRED YES)

# Use libstdc++ with Clang
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME} PRIVATE -stdlib=libstdc++)
  target_link_options(${PROJECT_NAME} PRIVATE -stdlib=libstdc++)
endif()

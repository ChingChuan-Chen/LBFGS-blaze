cmake_minimum_required(VERSION 3.16)

project("lbfgs_blaze")

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -fPIC")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include_directories(
    include
    ${CMAKE_CURRENT_SOURCE_DIR}/blaze
)

add_executable(${PROJECT_NAME} src/lbfgs_example.cpp)

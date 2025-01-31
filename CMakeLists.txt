set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable optimizations
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

cmake_minimum_required(VERSION 3.12)
project(bignum)

add_library(bignum_lib
    Bignum.cpp
)

target_include_directories(bignum_lib PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(bignum main.cpp)
target_link_libraries(bignum PRIVATE bignum_lib)
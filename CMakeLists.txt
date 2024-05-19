cmake_minimum_required(VERSION 3.22)
project(
    cars5
    VERSION 0.0.0
    DESCRIPTION "cars"
    LANGUAGES CXX
    
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(cars)

set(sources 
    src/ops.cpp
)

target_sources(cars PRIVATE ${sources})
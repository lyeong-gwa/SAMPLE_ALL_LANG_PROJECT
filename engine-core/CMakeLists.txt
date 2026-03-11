cmake_minimum_required(VERSION 3.16)
project(DeliveryHubEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(delivery_engine
    src/main.cpp
    src/matching_engine.cpp
    src/route_optimizer.cpp
)

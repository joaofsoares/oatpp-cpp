cmake_minimum_required(VERSION 3.26.4)
project(oatpp_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(oatpp_cpp src/main.cpp)

find_package(oatpp 1.3.0 REQUIRED)

target_link_libraries(oatpp_cpp
        PUBLIC oatpp::oatpp
)

target_include_directories(oatpp_cpp PUBLIC src)
cmake_minimum_required(VERSION 3.20)
project(moddash_mod VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Tells the compiler to look at your 2 C++ files
add_library(${PROJECT_NAME} SHARED src/main.cpp src/utils.cpp)

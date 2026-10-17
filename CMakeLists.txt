cmake_minimum_required(VERSION 3.14)
project(ModDash VERSION 1.0.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Header Include Paths (Tells CMake where your .hpp and .h files live)
include_directories(include)
include_directories(include/cocos2dx)

# 2. Source Files (Explicitly tracking your source files)
set(SOURCES
    main.cpp
    utils.cpp
)

# Optional: If you have extra source files inside your src/ folder, uncomment the line below:
# file(GLOB_RECURSIVE EXTRA_SOURCES "src/*.cpp")

# 3. Build Target (Compiles everything into a shared library for GD)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${EXTRA_SOURCES})

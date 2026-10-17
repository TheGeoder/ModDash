cmake_minimum_required(VERSION 3.14)
project(ModDash VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Header Include Paths
include_directories(include)
include_directories(include/cocos2dx)

# 2. Source Files (FIXED: Added the src/ folder path)
set(SOURCES
    src/main.cpp
    src/utils.cpp
)

# 3. Build Target
add_library(${PROJECT_NAME} SHARED ${SOURCES})

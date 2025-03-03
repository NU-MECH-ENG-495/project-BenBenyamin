cmake_minimum_required(VERSION 3.10)
project(CPP_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find all .cpp files in the src directory
file(GLOB SOURCES "*.cpp")

# Create the executable
add_executable(CPP_Project ${SOURCES})

# Include the src directory for headers
target_include_directories(CPP_Project PRIVATE src)

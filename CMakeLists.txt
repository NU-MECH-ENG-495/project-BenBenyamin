cmake_minimum_required(VERSION 3.10)
project(CPP_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add debug-specific compiler options
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Find all .cpp files in the src directory
file(GLOB SOURCES "*.cpp")

# Create the executable
add_executable(CPP_Project ${SOURCES})

# Include the src directory for headers
target_include_directories(CPP_Project PRIVATE src)

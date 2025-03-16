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

# Find OpenMP package
find_package(OpenMP REQUIRED)

# Include OpenMP flags for C++
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

# Automatically collect all .cpp files in the src directory for the 'graphics' library
file(GLOB GRAPHICS_SOURCES "src/*.cpp")

# Add the graphics library with automatically collected source files
add_library(graphics ${GRAPHICS_SOURCES})

# Link OpenMP to the graphics library
target_link_libraries(graphics PUBLIC OpenMP::OpenMP_CXX)

target_include_directories(graphics PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Create the executable
add_executable(CPP_Project src/main.cpp)

# Link OpenMP to the executable
target_link_libraries(CPP_Project PRIVATE graphics OpenMP::OpenMP_CXX)
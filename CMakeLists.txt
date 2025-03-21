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

include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the graphics library with automatically collected source files
add_library(graphics 
src/Canvas.cpp
src/linalg.cpp
src/stl.cpp
src/TriangleSurface.cpp
src/TriangleObject.cpp
)

target_include_directories(graphics PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Create the executable
add_executable(CPP_Project src/main.cpp)

target_link_libraries(CPP_Project PRIVATE graphics)

# Enable testing
enable_testing()
# Add the tests subdirectory
add_subdirectory(test)
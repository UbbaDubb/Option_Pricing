cmake_minimum_required(VERSION 3.15)
project(Option_Pricing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# Fetch Boost.Math as a ZIP archive (no git required)
FetchContent_Declare(
  boost_math
  URL https://github.com/boostorg/math/archive/refs/tags/boost-1.86.0.zip
)

FetchContent_MakeAvailable(boost_math)

# Your includes
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# Add Boost.Math headers
include_directories(${boost_math_SOURCE_DIR}/include)

# Sources
set(SOURCES
    src/Option.cpp
    src/EuropeanOption.cpp
    src/main.cpp
    src/MeshParameterGenerator.cpp
    src/MatrixPricer.cpp
)

# Executable
add_executable(Option_Pricing ${SOURCES})

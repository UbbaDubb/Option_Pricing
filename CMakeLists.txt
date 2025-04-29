cmake_minimum_required(VERSION 3.15)
project(OptionPricing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# Add Boost (assuming it's inside external/)
add_subdirectory(external/boost-math)

# Find all source files automatically
#file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SOURCES
    src/Option.cpp
    src/EuropeanOption.cpp
    src/main.cpp
)

# Create executable
add_executable(OptionPricing ${SOURCES})

# Link Boost
target_include_directories(OptionPricing PRIVATE external/boost-math/include)
target_link_libraries(OptionPricing PRIVATE Boost::math)

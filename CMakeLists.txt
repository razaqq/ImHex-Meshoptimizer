cmake_minimum_required(VERSION 3.20)
project(meshoptimizer)

if (NOT DEFINED ENV{IMHEX_SDK_PATH})
    message(FATAL_ERROR "The IMHEX_SDK_PATH environment variable is not set")
elseif ($ENV{IMHEX_SDK_PATH} STREQUAL "")
    message(FATAL_ERROR "The IMHEX_SDK_PATH environment variable is set but empty")
elseif (NOT EXISTS $ENV{IMHEX_SDK_PATH})
    message(FATAL_ERROR "The IMHEX_SDK_PATH environment variable doesn't contain a valid path")
endif()
add_subdirectory($ENV{IMHEX_SDK_PATH} ImHexSDK)

find_package(meshoptimizer REQUIRED)
add_imhex_plugin(
    NAME
        meshoptimizer
    SOURCES
        source/meshoptimizer.cpp
    LIBRARIES
        pl::libpl
        meshoptimizer::meshoptimizer
)
set_target_properties(meshoptimizer
    PROPERTIES
    CMAKE_CXX_STANDARD 23
    CMAKE_CXX_STANDARD_REQUIRED true
)

# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define project name
project(librosa_cpp)

add_definitions("-DXXX")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(LIBROSA_CPP_DIR LibrosaCpp)
include_directories(${LIBROSA_CPP_DIR})

aux_source_directory(test TEST_DIR)

add_executable(test  ${TEST_DIR})

target_link_libraries(test LINK_PRIVATE -ldl)

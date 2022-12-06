cmake_minimum_required(VERSION 3.21.0)
project(cpp-study VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2.1\ overloaded\ function\ principle)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2.3.1\ Visitor\ Pattern)


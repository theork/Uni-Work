PROJECT(ICP3038-Assignment1)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Useful in case you want to use std::min and std::max with 
# MS Visual C++
IF (MSVC)
   ADD_DEFINITIONS(-DNOMINMAX)
ENDIF (MSVC)

# Where the header files are
INCLUDE_DIRECTORIES(include)

# The program
ADD_EXECUTABLE(assignment1
    include/Image.h
    src/Image.cpp
    src/test.cpp)


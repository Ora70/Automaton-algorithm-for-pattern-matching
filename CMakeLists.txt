cmake_minimum_required(VERSION 3.20)
project(kmp)

set(CMAKE_CXX_STANDARD 17)

add_executable(kmp main.cpp Algorithm.h Naive.h ReadFile.cpp ReadFile.h Test.cpp Test.h GetData.cpp GetData.h)

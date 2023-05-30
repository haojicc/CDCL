cmake_minimum_required(VERSION 3.23)
project(CDCL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CDCL main.cpp util.cpp util.h satSolver.cpp satSolver.h)

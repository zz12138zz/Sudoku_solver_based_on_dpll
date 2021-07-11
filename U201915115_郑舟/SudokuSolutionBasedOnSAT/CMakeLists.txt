cmake_minimum_required(VERSION 3.17)
project(SoukouSolutionBasedOnSAT C)

set(CMAKE_C_STANDARD 99)

add_executable(SoukouSolutionBasedOnSAT main.c def.h cnfparser.c solver.c sudoku.c sudoku.h)
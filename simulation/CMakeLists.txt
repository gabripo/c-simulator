cmake_minimum_required (VERSION 3.5)

add_library(OdeSolver ode_solver.c)
add_executable(OdeSolverTest ode_solver_test.c)
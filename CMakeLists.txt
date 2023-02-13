cmake_minimum_required(VERSION 3.17)
project(EvilHangman)

set(CMAKE_CXX_STANDARD 14)


add_executable(EvilHangman_solution EvilHangman.cpp FamilySet.cpp)
add_executable(FamilySet_Tests unit_tests/FamilySet_Tests.cpp FamilySet.cpp FamilySet.h)


if (APPLE)
    set_property(TARGET EvilHangman_solution PROPERTY CXX_STANDARD 11)
    set_property(TARGET FamilySet_Tests PROPERTY CXX_STANDARD 11)
endif()
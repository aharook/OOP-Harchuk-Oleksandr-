cmake_minimum_required(VERSION 3.14)
project(AgeCalcTests)

set(CMAKE_CXX_STANDARD 14)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(runTests ageCalc.cpp)

target_link_libraries(runTests gtest_main)
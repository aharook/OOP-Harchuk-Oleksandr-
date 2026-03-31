cmake_minimum_required(VERSION 3.14)
project(Lab31_Moq_Cpp)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lab31vN_tests FileService.cpp Gmoqtests.cpp)

target_link_libraries(lab31vN_tests gtest_main gmock_main)
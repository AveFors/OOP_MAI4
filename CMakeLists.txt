cmake_minimum_required(VERSION 3.10)
project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library(figures_headers INTERFACE)
target_include_directories(figures_headers INTERFACE Laba4/headlines)



add_executable(main_app main.cpp)
target_link_libraries(main_app PRIVATE figures_headers)



include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY FALSE
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(test_figures Laba4/tests/test_main.cpp)
target_link_libraries(test_figures PRIVATE figures_headers gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(test_figures)
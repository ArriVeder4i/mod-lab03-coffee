cmake_minimum_required(VERSION 3.10)
project(VendingMachine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(vending_machine
    src/main.cpp
    src/Automata.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests
    test/tests.cpp
    src/Automata.cpp
)

target_link_libraries(run_tests GTest::gtest_main)

add_test(NAME AutomataTests COMMAND run_tests)
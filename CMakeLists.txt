cmake_minimum_required(VERSION 3.21)
project(hua5_test_task)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(tests
        src/crawler.cpp
        tests/tests.cpp
        )

cmake_minimum_required(VERSION 3.18)

project(libtrino)
set(CMAKE_MACOSX_RPATH 1)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(libtrino_tests integration/test_query_runner.cpp)
target_link_libraries(libtrino_tests gtest_main libtrino)
target_include_directories(libtrino_tests PRIVATE ..)
include(GoogleTest)
gtest_discover_tests(libtrino_tests)
cmake_minimum_required(VERSION 3.18)
project(libtrino)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(abrisan/trino)
add_subdirectory(tests)
add_executable(sample_main main.cpp)
target_link_libraries(sample_main PRIVATE libtrino)
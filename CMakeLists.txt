cmake_minimum_required(VERSION 3.21)
project(trino_lib)

set(CMAKE_CXX_STANDARD 23)
add_subdirectory(abrisan/trino)
add_executable(trino_lib main.cpp)
target_link_libraries(trino_lib PRIVATE libtrino)
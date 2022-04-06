cmake_minimum_required(VERSION 3.18)
project(libtrino)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 6ea2dec23c3df14ac3b27b7d2d6bbff0cb7ba1b0)
FetchContent_MakeAvailable(cpr)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(libtrino Connection.h Request.h TrinoJsonWrapper.h Result.cpp Result.h TrinoTypes.h Connection.cpp TrinoTypes.cpp CompatibleHttpClient.h DefaultHttpClient.cpp DefaultHttpClient.h)
target_link_libraries(libtrino PUBLIC cpr nlohmann_json::nlohmann_json)
set_target_properties(libtrino PROPERTIES LINKER_LANGUAGE CXX)
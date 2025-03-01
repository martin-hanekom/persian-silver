cmake_minimum_required(VERSION 3.31.5)
project(PersianSilver LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(PersianSilver ${SOURCES})

target_link_libraries(PersianSilver PRIVATE SFML::Graphics)
# SFML::Audio SFML::Network)
#target_link_libraries(PersianSilver PRIVATE src)

target_include_directories(PersianSilver PRIVATE ${CMAKE_SOURCE_DIR}/include)
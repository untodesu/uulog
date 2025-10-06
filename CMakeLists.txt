cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(uulog VERSION 1.0.0 LANGUAGES CXX)

option(UULOG_EXAMPLES "Build example applications" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(uulog
    "${CMAKE_CURRENT_LIST_DIR}/uulog/uulog.hh"
    "${CMAKE_CURRENT_LIST_DIR}/uulog/uulog.cc")
target_compile_definitions(uulog PRIVATE UULOG_DLLPRIVATE)
target_compile_features(uulog PUBLIC cxx_std_20)
target_include_directories(uulog PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

if(MSVC AND MSVC_VERSION GREATER_EQUAL 1914)
    # untodesu: I am not going to debate wheter it was a good idea on MSVC developers' side
    # to do this mainly because it was definitely not a good idea; who in their righteous mind would
    # fix a "C++20 compiler refuses to compile C++98 source" problem by... just forcing __cplusplus value
    # to be equal to 199711L unless forced to behave like a normal compiler with an option?!
    # https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus
    target_compile_options(uulog PUBLIC /Zc:__cplusplus)
endif()

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(uulog PUBLIC UULOG_STATIC)
endif()

if(UULOG_EXAMPLES)
    add_subdirectory(examples)
endif()

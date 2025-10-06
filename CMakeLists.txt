cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(uulog VERSION 1.0.0 LANGUAGES CXX)

option(UULOG_EXAMPLES "Build example applications" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(uulog
    "${CMAKE_CURRENT_LIST_DIR}/uulog/uulog.hh"
    "${CMAKE_CURRENT_LIST_DIR}/uulog/uulog.cc")
target_compile_features(uulog PUBLIC cxx_std_20)
target_include_directories(uulog PUBLIC "${CMAKE_CURRENT_LIST_DIR}/uulog")

if(BUILD_SHARED_LIBS)
    target_compile_definitions(uulog PUBLIC UULOG_DLL)
    target_compile_definitions(uulog PRIVATE UULOG_DLLPRIVATE)
endif()

if(UULOG_EXAMPLES)
    add_subdirectory(examples)
endif()

cmake_minimum_required(VERSION 3.26)
project(catalyst)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions($<$<CONFIG:Debug>:_DEBUG>)

add_subdirectory(Engine)
add_subdirectory(Editor)
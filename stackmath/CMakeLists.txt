cmake_minimum_required(VERSION 3.14)

project(stackmath LANGUAGES CXX)

set(SOURCE
    stackmath.cxx
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>: -g -O0 -Wall -Wextra>
    $<$<CONFIG:Release>: -O2>
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

cmake_minimum_required(VERSION 3.14)

project(stackmath LANGUAGES CXX)

set(SOURCE_DIR src)

set(SOURCE
    ${SOURCE_DIR}/stackmath.cc
    ${SOURCE_DIR}/Lexer.cc
    ${SOURCE_DIR}/Executor.cc
    ${SOURCE_DIR}/opcodes.cc
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>: -g -O0 -Wall -Wextra -Wpedantic -Werror -Wsign-conversion -Wfloat-equal -Wdouble-promotion>
    $<$<CONFIG:Release>: -O2>
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}
)

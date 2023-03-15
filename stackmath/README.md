# StackMath

My little interpreter-like stack calculator.

## Build

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

## Example:

This code is equal to sin(x) + cos(x):

    DUP
    SIN
    SWAP
    COS
    ADD
    STOP

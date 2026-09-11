#!/bin/bash

cmake \
    -S . \
    -B build \
    -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=cmake/avr.cmake
cmake --build build

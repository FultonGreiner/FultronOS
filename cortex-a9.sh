#!/usr/bin/env bash

# Rebuild the project
rm -rf Debug
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make -C Debug VERBOSE=1

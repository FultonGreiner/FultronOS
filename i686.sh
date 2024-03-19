#!/usr/bin/env bash

# Rebuild the project
rm -rf Debug
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/i686-elf-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make -C Debug VERBOSE=1

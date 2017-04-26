#!/bin/sh

# Create build directory if needed and cd into it
mkdir --verbose --parents ./build && cd ./build

# Create makefile and compile project
cmake .. && make -j4

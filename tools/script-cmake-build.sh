#!/bin/bash

if ! command -v cmake &> /dev/null
then
    echo "CMake could not be found. Install it or make it visible under the PATH."
    exit
fi

mkdir -p ../build
cd ../build
cmake .. && make

#!/bin/bash

if ! command -v meson &> /dev/null
then
    echo "Meson or python3 could not be found. Install it or make it visible under the PATH."
    exit
fi

cd ..
meson setup build && cd build
meson compile

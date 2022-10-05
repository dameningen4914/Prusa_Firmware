#!/bin/sh
set -xe
export PATH=$PWD/.dependencies/cmake-3.22.5/bin:$PATH
export PATH=$PWD/.dependencies/ninja-1.10.2:$PATH
rm -rf build
mkdir build
cd build
cmake .. -CCMAKE_TOOCHAIN_FILE="../cmake/LocalAvrGcc.cmake" -G Ninja
ninja ALL_FIRMWARE

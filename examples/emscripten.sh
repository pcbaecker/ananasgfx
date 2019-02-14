#!/bin/sh

### Create build directory
mkdir -p cmake-build-emscripten
cd cmake-build-emscripten

### Copy resource folder
cp -r ../resource examples/resource

### Execute cmake
emcmake cmake ../..

### Execute make
make AnanasGfxExamples
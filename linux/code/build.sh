#!/bin/bash

pushd ../build
g++ -o fph ../code/fph.cpp -lSDL -lSDL_image
popd
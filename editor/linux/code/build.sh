#!/bin/bash

pushd ../build
g++ -o editor ../code/editor.cpp ../code/timer.cpp ../code/utils.cpp ../code/main_screen.cpp -lSDL -lSDL_image
popd
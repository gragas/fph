#!/bin/bash

pushd ../build
g++ -o fph ../code/fph.cpp ../code/timer.cpp ../code/utils.cpp ../code/main_menu.cpp -lSDL -lSDL_image
popd
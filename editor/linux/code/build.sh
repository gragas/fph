#!/bin/bash

pushd ../build
g++ -std=gnu++11 -g -o editor ../code/editor.cpp ../code/timer.cpp ../code/utils.cpp ../code/main_screen.cpp ../code/text.cpp ../code/text_utils.cpp ../code/text_input.cpp -lSDL -lSDL_image
popd
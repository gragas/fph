#!/bin/bash

pushd ../build
g++ -std=gnu++11 -o fph ../code/fph.cpp ../code/timer.cpp ../code/utils.cpp ../code/main_menu.cpp ../code/button.cpp ../code/load.cpp ../code/text.cpp ../code/text_utils.cpp ../code/text_input.cpp ../code/map_utils.cpp ../code/character_creation_screen.cpp ../code/solo_game.cpp ../code/player.cpp -lSDL -lSDL_image
popd
#include "SDL/SDL.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

extern SDL_Surface *i_splash_background;
extern SDL_Surface *i_splash_title;

bool l_main_menu();

bool f_main_menu();

void logic_main_menu( SDL_Event& );

void b_main_menu( SDL_Surface* );

#endif

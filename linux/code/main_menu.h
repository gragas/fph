#include "SDL/SDL.h"
#include "button.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

class Main_Menu
{
 private:
  static SDL_Surface *i_background;
  static SDL_Surface *i_title;
  static Button exit_button;
  
 public:
  static bool load();
  static bool free();
  static void logic( SDL_Event& );
  static void blit( SDL_Surface*);
};

#endif

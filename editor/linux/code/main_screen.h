#include "SDL/SDL.h"
#include "text.h"

#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

class Main_Screen
{
 private:
  static SDL_Surface *i_background;
  static SDL_Surface *i_red_select_square;
  static unsigned int uint_selection;
  static Text t_filename;
  
 public:
  static bool load();
  static bool free();
  static void logic( SDL_Event& event );
  static void blit( SDL_Surface* screen );
};

#endif

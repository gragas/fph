#include "SDL/SDL.h"

#ifndef LOAD_H
#define LOAD_H

class Load
{
 private:
  static SDL_Surface *i_background;
  
 public:
  static bool load();
  static bool free();
  static void logic( SDL_Event& event );
  static void blit( SDL_Surface* screen );
};

#endif

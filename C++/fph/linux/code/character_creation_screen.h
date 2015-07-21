#include "SDL/SDL.h"

#ifndef CHARACTER_CREATION_SCREEN_H
#define CHARACTER_CREATION_SCREEN_H

class CharacterCreationScreen
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

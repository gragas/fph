#include "SDL/SDL.h"
#include <string>

#ifndef SOLO_GAME_H
#define SOLO_GAME_H

class SoloGame
{
 private:
  static SDL_Surface * i_background;
  
 public:
  static bool load( std::string character_name );
  static bool free();
  static void logic( SDL_Event& event );
  static void blit( SDL_Surface* screen );
};

#endif

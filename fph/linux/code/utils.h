#include "SDL/SDL.h"
#include <string>

#ifndef UTILS_H
#define UTILS_H

namespace utils
{
  extern const int SCREEN_WIDTH;
  extern const int SCREEN_HEIGHT;
  extern const int SCREEN_BPP;
  extern const int FRAMES_PER_SECOND;
  extern const bool CAP_FRAME_RATE;

  extern bool quit;

  extern void (*logic)( SDL_Event& event );
  extern void (*blit)( SDL_Surface* screen );

  SDL_Surface *load_image( std::string filename );
  void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);
  void clear( SDL_Surface* screen );
  void clearA( SDL_Surface* screen );
}

#endif

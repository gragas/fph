#include "SDL/SDL.h"
#include "text.h"
#include <array>
#include <string>

#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

namespace text_utils
{
  extern std::array<SDL_Surface*, 390> chars; // numeric, lower, upper
  extern int counter;
  void load( std::string path );
  void init();
}

#endif

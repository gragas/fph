#include "SDL/SDL.h"
#include "text.h"
#include <array>

#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

namespace text_utils
{
  extern std::array<SDL_Surface*, 62> chars; // numeric, lower, upper
  void init();
}

#endif

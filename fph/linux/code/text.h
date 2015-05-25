#include "SDL/SDL.h"
#include <string>

#ifndef TEXT_H
#define TEXT_H

class Text
{
private:
  std::string text;
  int x, y;
  SDL_Surface* i_text;

public:
  Text();
  void init( std::string text, int size, int color, int x, int y );
  std::string get_text();
  void free();
  void blit( SDL_Surface* screen );
};

#endif

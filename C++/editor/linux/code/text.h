#include "SDL/SDL.h"
#include <string>

#ifndef TEXT_H
#define TEXT_H

class Text
{
private:
  std::string text;
  int size, color, x, y;
  SDL_Surface* i_text;

public:
  Text();
  void init( std::string text, int size, int color, int x, int y );
  std::string get_text();
  void set_text( std::string text );
  int get_size();
  int get_color();
  int get_x();
  int get_y();
  void free();
  void blit( SDL_Surface* screen );
};

#endif

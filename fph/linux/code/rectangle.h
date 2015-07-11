#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "SDL/SDL.h"

class Rectangle
{
private:
  int x, y;
  int w, h;
  Uint8 r, g, b, a;
  SDL_Surface * surface;

public:
  Rectangle( int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a );
  void render();
  void overlay( int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a );
  void blit( SDL_Surface * destination );
  void blit( SDL_Surface * destination, int x, int y );
};

#endif

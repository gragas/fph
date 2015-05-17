#include "SDL/SDL.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
  SDL_Rect box;
  
public:
  Button( int x, int y, int w, int h );
  void draw();
}

#endif

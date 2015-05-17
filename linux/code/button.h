#include "SDL/SDL.h"
#include <string>

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
  SDL_Surface* pressed_surface;
  SDL_Surface* unpressed_surface;
  SDL_Rect box;
  int x, y;
  
public:
  Button( int x, int y, std::string filename1, std::string filename2 );
  bool contains( int x, int y );
  void draw( int mouse_x, int mouse_y, bool mouse_down, SDL_Surface* screen );
};

#endif

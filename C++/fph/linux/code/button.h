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
  bool mouse_down;
  
public:
  bool within;
  Button();
  void init( int x, int y, std::string filename1, std::string filename2, bool centered=true );
  void update( bool mouse_down );
  void draw( SDL_Surface* screen );
  void free();
};

#endif

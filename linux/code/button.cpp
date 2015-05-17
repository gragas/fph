#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include "button.h"
#include "utils.h"

Button::Button()
{
  
}

void Button::init( int x,  int y, std::string filename1, std::string filename2, bool centered )
{
  box.x = x;
  box.y = y;
  pressed_surface = load_image( filename1 );
  unpressed_surface = load_image( filename2 );
  box.w = pressed_surface->w;
  box.h = pressed_surface->h;
  if( centered )
  {
    box.x -= box.w / 2;
    box.y -= box.h / 2;
  }
}

void Button::update( int mouse_x, int mouse_y )
{
  this->mouse_x = mouse_x;
  this->mouse_y = mouse_y;
  within = ( mouse_x > box.x && mouse_x < box.x + box.w && mouse_y > box.y && mouse_y < box.y + box.h );
}

void Button::update( bool mouse_down )
{
  this->mouse_down = mouse_down;
}

void Button::draw( SDL_Surface* screen )
{
  if( within && mouse_down )
  {
    apply_surface( box.x, box.y, pressed_surface, screen );
  }
  else
  {
    apply_surface( box.x, box.y, unpressed_surface, screen );
  }
}

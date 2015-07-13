#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include "button.h"
#include "utils.h"

Button::Button(){}

void Button::init( int x,  int y, std::string filename1, std::string filename2, bool centered )
{
  box.x = x;
  box.y = y;
  pressed_surface = utils::load_image( filename1 );
  unpressed_surface = utils::load_image( filename2 );
  box.w = pressed_surface->w;
  box.h = pressed_surface->h;
  if( centered )
  {
    box.x -= box.w / 2;
    box.y -= box.h / 2;
  }
}

void Button::update( bool mouse_down )
{
  this->mouse_down = mouse_down;
  within = (utils::mouse_x > box.x) &&
           (utils::mouse_x < box.x + box.w) && 
	   (utils::mouse_y > box.y) && 
           (utils::mouse_y < box.y + box.h);
}

void Button::draw( SDL_Surface* screen )
{
  if( within && mouse_down )
  {
    utils::apply_surface( box.x, box.y, pressed_surface, screen );
  }
  else
  {
    utils::apply_surface( box.x, box.y, unpressed_surface, screen );
  }
}

void Button::free()
{
  SDL_FreeSurface( pressed_surface );
  SDL_FreeSurface( unpressed_surface );
}

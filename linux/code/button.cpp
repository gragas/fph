#include "SDL/SDL.h"
#include <string>
#include "button.h"
#include "utils.h"

Button::Button( int x,  int y, std::string filename1, std::string filename2 )
{
  box.x = x;
  box.y = y;
  pressed_surface = load_image( filename1 );
  unpressed_surface = load_image( filename2 );
  box.w = pressed_surface->w;
  box.h = pressed_surface->h;
}

bool Button::contains( int x, int y )
{
  return x < box.x + box.w && x > box.x && y < box.y + box.h && y > box.y;
}

void Button::draw( int mouse_x, int mouse_y, bool mouse_down, SDL_Surface* screen )
{
  if( contains( mouse_x, mouse_y ) && mouse_down )
  {
    apply_surface( x, y, pressed_surface, screen );
  }
  else
  {
    apply_surface( x, y, unpressed_surface, screen );
  }
}
